#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "【昊天塔内】" NOR);
        set("long", HIR @LONG

              昊     天     塔      内

    这里是昊天塔内，四周无任何出口，但见塔壁光彩耀眼，
似乎蕴藏着极大的力量。

LONG NOR );

        set("sky", 1);
        setup();
}

void init()
{     
       string msg = HIM "塔内放射出耀眼的光芒，令你无法睁开双眼 ……\n" NOR;
       
       msg += HIG "数道光芒将你团团围住，似乎要钻入你的七窍之内 ……\n" NOR;
       msg += HIY "慢慢地你觉得自己渐渐地与肢体分离，意识也渐渐模糊 ……\n" NOR;
       msg += HIR "正当你快要失去知觉的时候，七彩光芒将你卷出了昊天塔 ……\n" NOR;
       msg += HIW "你感觉你在时空中穿梭许久，浑身无法动弹，意识也在逐渐模糊，\n"
                  "渐渐地，你再也想不起自己身在何处，为何会来到这里，自己又\n"
                  "是谁，将要到何方 ……\n\n" NOR;

       tell_object(this_object(), msg);
       return;
}
