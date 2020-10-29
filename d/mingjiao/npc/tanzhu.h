// tanzhu.h for join mingjiao 

#include "mingjiao.h"

int do_join(string arg)
{
        object me, ob, obj;
        mapping family;

        me = this_object () ;
        ob = this_player () ;

        if( !arg || arg!="mingjiao" )
                return notify_fail("你要加入什么组织？\n"); 
           if( query_temp("have_letter", ob) || present("tuijian xin1",ob) )
           {
                command("say 好啊。");
                command("heihei "+query("id", ob));
                return 1;
        }
        if( !mapp(family=query("family", ob)) || 
            !query("family/family_name", ob) )
           {
                message_vision("$N点点头，对$n说道：好，你到昆仑山总舵去找接引使，他会让你入教的。\n",me,ob);
                message_vision("$N交给$n一封推荐信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/mingjiao/obj/tuijianxin-1");
                obj->move(ob);
                return 1;        
        }
           if( family["family_name"] != "明教" )
        {
                message_vision("$N摇摇头，对$n说道：你已经加入其他门派了，不能再入我光明圣教。\n",me,ob);
                return 1;
        }
        else
                message_vision("$N摇摇头，对$n说道：你已经是我明教的人了。\n",me,ob);
        return 1;
}
