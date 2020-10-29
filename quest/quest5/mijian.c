#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"军机密件"NOR, ({ "mi jian"}));
        set_weight(10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "封");
                set("long",
                        "一封军机密件,记载着襄阳城守军的兵力部署。\n");
                set("value", 0);
                set("material", "paper");
                 
         }
}
void init()
{    
        add_action("do_xiaohui", "xiaohui");
}

int do_xiaohui(string arg)
{
        int i,exp,pot,count,base_exp,add_exp;
        object ob,me,*team;
              
                me=this_player();
        ob=this_object();
                if(!arg||arg!="mi jian") return notify_fail("你要销毁什么？\n");
        if( query_temp("host", ob) != query("id", me )
                         || !me->query_condition("zzz_busy") || !query_temp("team_count", me) )
                return notify_fail("这件事好像和你没关系吧?\n");
                if (!present("mi jian",me) )
        return notify_fail("你身上没有密件。\n"); 
        //check ok
                message_vision("$N从怀中掏出一只火折点燃了密件。\n"+HIR"只听「轰」的一声，密件在火中慢慢化为灰烬 。\n"NOR, me);
        count=query_temp("team_count", me);
                if (count<2) count=2;        
       base_exp=3000/count;
                team=me->query_team();
                count=sizeof(team);
                //write("\n"+sprintf("%d",count));
                for(i=0;i<count;i++)
                { if(team[i]!=0)
                {
                        if (team[i]->query_condition("zzz_busy"))
                        {if( !query("zzz_job_count", team[i]) )
                     set("zzz_job_count", 1, team[i]);
             else
                     addn("zzz_job_count", 1, team[i]);
                         add_exp=query("zzz_job_count", team[i])/10;
                     exp=base_exp+random(200)+add_exp;
                     pot=exp/3+random(100);
             addn("potential", pot, team[i]);
             addn("combat_exp", exp, team[i]);
                         tell_object(team[i],HIW"你被奖励了：\n" + 
                       chinese_number(exp) + "点实战经验\n" +
                       chinese_number(pot) + "点潜能\n"+
                       NOR);
                        }
                        } 
                }
                  delete_temp("team_count", me);
                   
                  destruct(this_object());
          return 1;
}