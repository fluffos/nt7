// toptenadd.c
#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string str,*astr,type;
        int i;
        mapping paiming;

        seteuid(geteuid(me));
        if (!arg||arg=="")
                  return notify_fail("指令格式 : topten 排行类型
目前的排行类型有：\n
        【"+LOCAL_MUD_NAME()+"】十大高手排行榜（gaoshou）
        【"+LOCAL_MUD_NAME()+"】十大新锐排行榜（xinrui）
        【"+LOCAL_MUD_NAME()+"】十大经验排行榜（exp）
        【"+LOCAL_MUD_NAME()+"】十大富翁排行榜（richman）
        【"+LOCAL_MUD_NAME()+"】十大内力排行榜（neili）
        【"+LOCAL_MUD_NAME()+"】十大精力排行榜（jingli）
        【"+LOCAL_MUD_NAME()+"】十大文豪排行榜（dushu）\n");

        if( time()-query_temp("last_topten", me)<1 )
              return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        if( !wizardp(me) )
        set_temp("last_topten", time(), me);
        if (arg=="gaoshou")
              type="gaoshou";
        else if(arg=="xinrui")
              type="xinrui";
        else if(arg=="exp")
        {
              // if (!wizardp(me)) return notify_fail("你无权查看这个项目。\n");
              type="exp";
        }
        else if(arg=="richman"||arg=="rich")
        {
              // if (!wizardp(me)) return notify_fail("你无权查看这个项目。\n");
              type="rich";
        }
        else if(arg=="neili")
              type="neili";
        else if(arg=="jingli")
              type="jingli";
        else if(arg=="dushu"||arg=="literate")
              type="dushu";
        else 
              type=arg;
        if (type == "gaoshou")
        {
                paiming = COMPETE_D->query_tops();
                str = HIC "      *          雄       霸       天       下          *\n"NOR;
                str += HIC "-------------------------------------------------------------\n";
                str += "\n";
                for (i = 0;i < sizeof(paiming);i++)
                {
                        str += HIY + "   【天下第" + chinese_number(i+1) + "】 " + NOR + 
                               paiming[i]["title"] + "\n";
                        str += "\n";
                }
                str += HIC "-------------------------------------------------------------\n";
        } else if (type == "xinrui")
        {
                paiming = XINRUI_D->query_tops();
                str = HIC "      *          旭       日       东       升          *\n"NOR;
                str += HIC "-------------------------------------------------------------\n";
                str += "\n";
                for (i = 0;i < sizeof(paiming);i++)
                {
                        str += HIY + "   【第" + chinese_number(i+1) + "新锐】 " + NOR + 
                               paiming[i]["title"] + "\n";
                        str += "\n";
                }
                str += HIC "-------------------------------------------------------------\n";
        } else str = TOPTEN_D->topten_query(type);
        write(str+"\n");
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : topten 排行类型
目前的排行类型有:
gaoshou  十大高手
xinrui   十大新锐
exp      十大经验[巫师查看]
richman  十大富翁[巫师查看]
neili    十大内力
jingli   十大精力
dushu    十大文采
HELP
    );
    return 1;
}
