// Room: /d/kunlun/bainiuling.c
// Last Modified by Lonely on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_wo(string arg);
int do_breathe();
void delete_done(object me);

void create()
{
        set("short", "白牛岭");
        set("long",@long
这座山岭因终年覆盖白雪，且形状远望犹如一头正在吃草的牛而得
名。这里寒风呼啸，凛冽刺骨，你不禁打了个寒颤。山顶有一处平地，
放有一块青色的巨石(stone)。
long);
        set("exits",([
                "southwest" : __DIR__"fufengshan",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "stone" :"这块巨石很大，可以躺下一个人。表面十分平整光滑，似乎常有人摩挲。\n",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119970);
        set("coor/y", 40180);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_wo", "wo");
        add_action("do_breathe", "breathe");
}

int do_wo(string arg)
{
        if ( !arg || (arg != "stone") )
        return notify_fail("你要卧在什么上面？\n");

        if (this_player()->is_busy())
                return notify_fail("你正忙着呢。\n");

        if( query_temp("marks/wo", this_player()) )
                return notify_fail("你已经躺在青石上了。\n");

        set_temp("marks/wo", 1, this_player());
        return notify_fail("你侧身躺于青石上，意守丹田，口眼轻闭，双腿自然微曲，全身放松。\n");
}

int do_breathe()
{
        object me=this_player();

        if( !query_temp("marks/wo", me) )
                return notify_fail("你深深吸了几口气，只觉得寒气冲进五脏六腑，体内的真气几乎提不起来。\n");

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if( query_temp("marks/done", me) )
                return notify_fail("寒风凛冽，你刚运过功，身子正十分虚弱，先好好休息一下吧。\n");

        if (me->query_skill("liangyi-shengong", 1) < 120 ) 
                return notify_fail("你内功基底太弱，不可以随意控制内息。\n");
                
        if (me->query_skill("liangyi-shengong", 1) > 199 ) 
                return notify_fail("你的两仪神功已经很强了，无法再通过吐纳来增强功力。\n"); 
                
        if (! me->can_improve_skill("liangyi-shengong")) 
                return notify_fail("你的实战经验不足，无法继续吐纳练功。\n"); 

        if (query("qi", me) < 40 || query("jing", me) < 40) 
                return notify_fail("你现在已经很疲倦了，休息一下再来吧息。\n"); 

        message_vision(HIW "\n$N" HIW "集聚体内的两仪真气，深深吸进几口气，又缓缓的将" 
                       "其呼出\n体外。$N" HIW "只觉得全身透彻清凉心定似水，仿佛已物我" 
                       "浑然一体。\n\n" NOR, me); 

        me->receive_damage("jing", random(30));
        me->receive_damage("qi",   random(30));
        if (me->can_improve_skill("liangyi-shengong")) 
                me->improve_skill("liangyi-shengong", 5 + query("int", me) / 2 + 
                                  me->query_skill("force") / 6); 

        set_temp("marks/done", 1, me);
        call_out("delete_done", 5, me);

        return 1;
}

void delete_done(object me)
{
        if( objectp(me))delete_temp("marks/done", me);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/wo", me);
        return ::valid_leave(me, dir);
}
