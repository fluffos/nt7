inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "深潭");
        set("long",
"[1;32m周围一片黑暗，大概已经深入地底了吧。藉着苔藓发出的幽\n"
"幽磷光，可以看到前方不远处有一个深潭(tan)，寒气逼人。\n"
);
        set("exits", ([ 
       "eastup" : __DIR__"spirit6",
        ]) );


        set("no_magic", 1);
        setup();
}


void init()
{
        add_action("do_look", "look");
        add_action("do_approach", "approach");
}

int do_look(string arg)
{
        object me;
        object room;
        me = this_player();
        if(!arg || arg != "深潭" && arg != "tan" ) return 0;
        switch ( random (2)) {
                case 0:
tell_object(me,"潭边长满了苔藓，还是不要靠（ａｐｐｒｏａｃｈ）的太近。\n"); 
                break;
                case 1:
message_vision("$N探头向潭里望去。 \n", me); 
tell_object(me,"黑不隆咚的潭水深不见底。 \n");
                break;
        }


        return 1;
}
int do_approach(string arg)
{
        object me;
        object room;
        me = this_player();
        if(!arg || arg != "深潭" && arg != "tan" ) return 0;
        switch ( random (3)) {
                case 0:
message_vision("$N走近深潭探头向里望去。 \n", me); 
tell_object(me,"潭水深不见底，不过你似乎可以听到底下流水的声音。 \n");
                break;
                case 1:
message_vision("$N走近深潭探头向里望去。哎呀！一不小心掉了进去！\n", me); 
message_vision("$N的头撞在潭壁上，一下子昏了过去！\n", me); 
                call_out("be_saved",8);
                me->unconcious();
                room = find_object(__DIR__"spirit10");
                 if(!objectp(room)) room=load_object(__DIR__"spirit10");
                me->move(room);
                break;
                case 2:
message_vision("$N走近深潭探头向里望去。哎呀！一不小心掉了进去！\n", me);
              room = find_object(__DIR__"underwater");
                if(!objectp(room)) room=load_object(__DIR__"underwater");
                me->move(room);
                break;
        }

        return 1;
}

int be_saved()
{   
            object me;            me=this_player();

            me->remove_call_out("revive");
            me->revive();
            me->reincarnate();
message_vision("$N慢慢清醒过来，发现自己在一间小屋中！\n", me); 
message_vision("一个美丽的精灵族女子看见$N恢复了知觉，关切地走了过来！\n", me);
           return 1;
}
