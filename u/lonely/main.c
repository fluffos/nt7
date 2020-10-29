int main(object me)
{
        mixed obs;
        mixed kk;
        mixed key;

        int i;
        int sz;
        obs = objects();
        //for(i=0;i<sizeof(obs);i++) {
        //      log_file("objects",sprintf("%O\n",obs[i]));
        //}
        sz = sizeof(obs);
        printf("total %d\n",sizeof(obs));
        kk = ([]);
        for(i=0;i<sz;i++) {
                kk[base_name(obs[i])] += 1;
        }
        key = keys(kk);
        sz = sizeof(key);
        printf("types=%O\n",sz);
        for(i=0;i<sz;i++) {
                reset_eval_cost();
                log_file("obs",key[i]+","+kk[key[i]]+"\n");
        }
        return 1;
}

