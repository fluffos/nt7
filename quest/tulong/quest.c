// 升职体系
// ask id about 功劳
#include <ansi.h>

string *tang=({
        HIG"火云座"NOR,
        HIG"赤云座"NOR,
        HIW"金云座"NOR,
        BLU"玄云座"NOR,
        YEL"土云座"NOR,
        HIG"莲花座"NOR,
        HIG"洪花座"NOR,
        HIW"百花座"NOR,
        BLU"太云座"NOR,
        YEL"宏云座"NOR,
        });

string *zhiwei=({
        GRN"副香主"NOR,
        HIG"香主"NOR,
        HIY"副堂主"NOR,
        HIW"堂主"NOR,
        HIY"教主"NOR,
        HIR"总教主"NOR,
        });

int find_zhiwei(int level);
string assume_tang(object ob,int level,int ttang);
int check_ob(object ob,int level);

int do_shengji(object ob)
{
        int t;
        int level=ob->query("tiandihui/level");

        switch(level)
        {
                case 0:
                        if(!check_ob(ob,0))
                                return 0;
                        if(!t=find_zhiwei(0))
                                return 0;
                        assume_tang(ob,0,t);
                        return 1;
                        break;
                case 1:
                        if(!check_ob(ob,1))
                                return 0;
                        if(!t=find_zhiwei(1))
                                return 0;
                        assume_tang(ob,1,t);
                        return 2;
                        break;
                case 2:
                        if(!check_ob(ob,2))
                                return 0;
                        if(!t=find_zhiwei(2))
                                return 0;
                        assume_tang(ob,2,t);
                        return 3;
                        break;
                case 3:
                        if(!check_ob(ob,3))
                                return 0;
                        if(!t=find_zhiwei(3))
                                return 0;
                        assume_tang(ob,3,t);
                        return 4;
                        break;
                case 4:
                        if(!check_ob(ob,4))
                                return 0;
                        if(!t=find_zhiwei(4))
                                return 0;
                        assume_tang(ob,4,t);
                        return 5;
                        break;
                case 5:
                        if(!check_ob(ob,5))
                                return 0;
                        if(!t=find_zhiwei(5))
                                return 0;
                        assume_tang(ob,5,t);
                        return 6;
                        break;
                case 6:
                        if(!check_ob(ob,6))
                                return 0;
                        if(!t=find_zhiwei(6))
                                return 0;
                        assume_tang(ob,6,t);
                        return 7;
                        break;
        }
}

int find_zhiwei(int level)
{
        object *us;
        int ttang,i;

        us=users();
        i=sizeof(us);
        ttang=random(sizeof(tang));
        
        while(i--)
        {
                if(((int)us[i]->query("level")==level)
                        && ((int)us[i]->query("tiandihui/tang")==ttang))
                {
                        write(CYN"云风里说道：我火云教现在没有合适的位置给你。\n"NOR);
                        return 0;
                }
        }
        return ttang;
}

int check_ob(object ob,int level)
{
        int exp,job;
        int lvl_exp,lvl_job;

        exp=ob->query("combat_exp");
        job=ob->query("tiandihui/job");
        
        switch(level)
        {
                case 0:
                        lvl_exp=100000;
                        lvl_job=400;
                        break;
                case 1:
                        lvl_exp=200000;
                        lvl_job=800;
                        break;
                case 2:
                        lvl_exp=600000;
                        lvl_job=1500;
                        break;
                case 3:
                        lvl_exp=1000000;
                        lvl_job=2200;
                        break;
                case 4:
                        lvl_exp=1600000;
                        lvl_job=3000;
                        break;
                case 5:
                        lvl_exp=2000000;
                        lvl_job=4200;
                        break;
                default:
                        lvl_exp=6000000;
                        lvl_job=1000000;
                        break;
        }

        if(exp<lvl_exp)
        {
                message_vision(
CYN"陈进南对$N"CYN"说道：你的经验太少，无法胜任"+zhiwei[level]+CYN"之职。\n"NOR,ob);
                return 0;
        }
        if(job<lvl_job)
        {
                message_vision(
CYN"云风里对$N"CYN"说道：论到贡献，我教中还有很多兄弟在你之上。我看你还无法胜任"+zhiwei[level]+CYN"一职。\n"NOR,ob);
                return 0;
        }
        return 1;
}

string assume_tang(object ob,int level,int ttang)
{
        message_vision(
CYN"云风里对着$N"CYN"点了点头道：不错，我天地会兄弟中数你尽职尽责，"+tang[ttang]+zhiwei[level]+CYN"之职就由你来担任吧。\n"NOR,ob);
        ob->set("tiandihui/tang",ttang);
        ob->add("tiandihui/level",1);
        ob->add("combat_exp",10000);
        ob->set("title",HIW"火云教"+tang[ttang]+zhiwei[level]);
        if(level>3)
                ob->set("title",HIW"火云教"+zhiwei[level]);
        message_vision(
"云风里从怀中取出一些银两说道：这些银两是你辛苦所得。\n",ob);
        MONEY_D->pay_player(ob,200000);
        return (HIW"火云教"+tang[ttang]+zhiwei[level]);
}


