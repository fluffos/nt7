
// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org (16/05/2008)

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me,string arg)
{
        int i, j;
        string *ks, *os;
        mapping all, data, temp;
        string msg = "";

        all  = FUBEN_D->query_fuben_all();
        data = FUBEN_D->query_fuben_data();

        ks = keys(all);
        for( i=0;i<sizeof(ks);i++ ) {
                temp=all[ks[i]];
                if( mapp(temp) && sizeof(temp) ) {
                        os = keys(temp);
                        for( j=0;j<sizeof(os);j++ )
                        {
                                if( os[j] != me->query_id(1) ) continue;
                                
                                msg += sprintf("副本名称：%-33s剩余时间：%s\n",
                                                data[ks[i]]["name"]+"<"+ks[i]+">("+os[j]+")",
                                                appromix_time(temp[os[j]] - time()) );
                        }
                }

        }

        if( sizeof(msg) < 1 )
        {
                write("你没有建立任何副本。\n");
                return 1;
        }
        
        me->start_more(msg);
        return 1;
}

