import java.io.*;

public class Main{
    static final int N=255;
    static int Case,n,m,k,i,j,x,y,now,ans,t;
    static int[] q=new int[N];
    static BIT vis=new BIT();
    static BIT[] g0=new BIT[N];
    static BIT[] g1=new BIT[N];

    static class BIT{
        int[] v=new int[8];
        void clear(){for(int i=0;i<8;i++)v[i]=0;}
        void set(int x){v[x>>5]|=(1<<(x&31));}
        void flip(int x){v[x>>5]^=(1<<(x&31));}
        int get(int x){return (v[x>>5]>>(x&31))&1;}
    }

    static void flipedge(int x,int y){
        g0[x].flip(y);
        g1[y].flip(x);
    }

    static void dfs0(int x){
        vis.flip(x);
        for(int i=0;i<8;i++)while(true){
            int o=vis.v[i]&g0[x].v[i];
            if(o==0)break;
            dfs0((i<<5)|Integer.numberOfTrailingZeros(o));
        }
        q[++t]=x;
    }

    static void dfs1(int x){
        vis.flip(x);now++;
        for(int i=0;i<8;i++)while(true){
            int o=vis.v[i]&g1[x].v[i];
            if(o==0)break;
            dfs1((i<<5)|Integer.numberOfTrailingZeros(o));
        }
    }

    public static void main(String[] args)throws Exception{
        FastScanner in=new FastScanner(System.in);
        StringBuilder out=new StringBuilder();

        Case=1;
        while(Case-->0){
            n=in.nextInt();
            m=in.nextInt();

            for(i=0;i<n;i++){
                if(g0[i]==null)g0[i]=new BIT();
                if(g1[i]==null)g1[i]=new BIT();
                g0[i].clear();
                g1[i].clear();
            }

            for(i=0;i<n;i++){
                String s=in.next();
                for(j=0;j<n;j++)if(s.charAt(j)=='1')flipedge(i,j);
            }

            while(m-->0){
                k=in.nextInt();
                while(k-->0){
                    x=in.nextInt();
                    y=in.nextInt();
                    flipedge(x-1,y-1);
                }

                vis.clear();
                for(ans=i=0;i<n;i++)vis.set(i);
                for(t=i=0;i<n;i++)if(vis.get(i)!=0)dfs0(i);
                for(i=0;i<n;i++)vis.set(i);
                for(i=n;i>=0;i--)if(vis.get(q[i])!=0){
                    now=0;
                    dfs1(q[i]);
                    ans+=now*(now-1)/2;
                }
                out.append(ans).append('\n');
            }
        }

        System.out.print(out.toString());
    }

    static class FastScanner{
        private final InputStream in;
        private final byte[] buffer=new byte[1<<16];
        private int ptr=0,len=0;

        FastScanner(InputStream is){
            in=is;
        }

        private int read()throws IOException{
            if(ptr>=len){
                len=in.read(buffer);
                ptr=0;
                if(len<=0)return -1;
            }
            return buffer[ptr++];
        }

        int nextInt()throws IOException{
            int c=read();
            while(c<=32&&c!=-1)c=read();
            int x=0;
            while(c>32){
                x=x*10+c-'0';
                c=read();
            }
            return x;
        }

        String next()throws IOException{
            int c=read();
            while(c<=32&&c!=-1)c=read();
            if(c==-1)return null;
            StringBuilder sb=new StringBuilder();
            while(c>32){
                sb.append((char)c);
                c=read();
            }
            return sb.toString();
        }
    }
}
