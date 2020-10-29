//xdh_guard.c

inherit NPC;

#include <ansi.h>

int ask_xdh(object me, object ob);
void create()
{
        set_name("守卫",({"shou wei","guard"}) );
        set("long","这是一个年轻人，长的流里流气的。\n");
        set("title","小刀会帮众");
        set("gender","男性");
        set("age",20);
        set("combat_exp",100);
        set("inquiry",([
                "小刀会" : (: ask_xdh :),
        ]) );
        setup();
}

int ask_xdh(object me, object ob)
{
        
        me=this_player();
        ob=this_object();
        if( query("bunch/bunch_name", me) != "小刀会" )
        {
                command("grin");
                tell_object(me,"小刀会守卫说：“是想投奔咱们小刀会吧？那就得守规矩。”\n");
                tell_object(me,HIB"小刀会守卫用黑布蒙上你的眼睛，带着你七走八走，最后好象到了一
间屋子里面。\n你蒙着的黑布也被人取了下来。\n"NOR);
                tell_room("$N被带了进来。\n",me);
                me->move("/d/city/xdhzb");
                return 1;
        }
        if (good_bunch(me))
        {
                command("say 我们小刀会不欢迎你这种自命正派的人！请回吧。\n");
                return 1;
        }
        
        tell_object(me,"小刀会守卫奇怪道：“同为本帮兄弟，你何出此言啊？”\n");
        return 1;
}

        