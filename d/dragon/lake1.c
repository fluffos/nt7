inherit ROOM; 
#include <ansi.h> 
void create()
{
    set("short", "三清湖");
    set("long",
"[1;32m湖水清澈透明，不时可以看到几尾鱼跳上水面。湖水尽头是\n"
"一个大瀑布。在这里可以听到瀑布从山上直冲而下，发出的轰轰雷声。湖\n"
"边一块巨石，上写＂三清湖＂。[2;37;0m\n"
);
    set("item_desc", ([
        "清潭":  "清潭明澈见底，里面小鱼小虾皆若空游无所依。\n",
        "pond":  "清潭明澈见底，里面小鱼小虾皆若空游无所依。\n",
      ]));
    set("exits", ([ /* sizeof() == 4 */
        "north" : __DIR__"taolin", 
        "northwest" : __DIR__"pond", 
        "southwest" : __DIR__"lake2", 
        "west" : __DIR__"lake",
      ]));
}

void fish_notify(object obj, int i)
{
    object me, room, fish, *inv, bait;

    me = this_player();

    switch (i) { 
    case 0:
        bait = present("qiu yin", obj);
        if(!objectp(bait)) {
            message("vision",me->name() + "掏出了" + obj->name() + "又放了回去。\n", environment(me), me);
            tell_object(me, obj->name() + "上没有饵怎么可以钓鱼呢？ \n");
        }
        else {
            message_vision("$N挥动了一下，" + obj->name() + "在空中划了一道漂亮的弧线，鱼钩落入了水中。 \n" , me);
            destruct(bait);
            remove_call_out("do_fishing");              
            call_out("do_fishing", 5, me);
        }
        break;
    }
    return;
}

void do_fishing(object me)
{
    object       fish;

    if(me && environment(me) == this_object()) {
        message_vision("$N很快又扯动了一下鱼杆， " , me);
        switch (random(3)) {
        case 0:
            message_vision("却什么都没钓上来！ \n", me);
            break;
        case 1:
            message_vision("鱼怪被钓上来啦！！！！ \n", me); 
            fish = new("/quest/tulong/obj/fish1");
            set_temp("m_success/鱼怪", 1, me);
            fish->move(environment(me));
            remove_call_out("kill_me");
            call_out("kill_me", 1, me);         break;
        case 2:
            message_vision("鱼钩上钓着一条大鱼！！ \n", me);
            fish = new("/quest/tulong/obj/fish");
            fish->move(me);
            break;
        }
    }
    return;
}
