#include <ansi.h>
inherit ROOM; 
void create()
{
        int i;
        set("short", "书架顶");
        set("long", @LONG
书架顶上积满了厚厚的一层灰尘，书架顶和房梁还有三尺多高的
距离由于不经常打扫，这里步满了蜘蛛丝，书架顶的浮尘上还能依稀
见到一些爬虫留下的痕迹有时候有些小鸟也会在这里筑巢。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "down" : "/d/shaolin/cjlou1",
        ]));        

        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
        setup();
}

void init()
{ 
        add_action("do_pull", "qingsao");
        add_action("do_pull", "clear");
}

int do_pull()
{
        object ob, *obs, me = this_player();
        
        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");
                
        message_vision("$N仔细地打扫了书架顶上的灰尘,看上去干净多了。\n", me);
        me->start_busy(5);
        
        // obs = filter_array(children("/clone/book/yijinjing.c"), (: clonep :));
        // if (query("bamboo_count") > 0 && sizeof(obs) < 3) 
        if (query("bamboo_count") > 0)
        {
                    ob = new("/clone/book/yijin_book"); 
                ob->move(me, 1);
                addn("bamboo_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s搞到了少林镇寺之宝易筋经秘籍啦。",query("name", me)));
        } else
        if (query("yijinjing_count") > 0)
        {
                if (random(2)) ob = new("/clone/book/yjj_book2");
                else ob = new("/clone/book/yijinjing");
                ob->move(me, 1);
                addn("yijinjing_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s搞到了少林镇寺之宝易筋经残谱啦。",query("name", me)));
        }
        return 1;
}

void reset()
{
        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
}
