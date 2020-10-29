inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草原");
        set("long", @LONG
这里已经渐渐接近蒙古军营了，大军行到此处，眼前陡然开阔起
来，放眼望去，四处都是茫茫大草海，让人不由心生出一种凄凉而豪
壮的感觉。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "east"  : __DIR__"shanlu3",
                "west"  : __DIR__"shanlu3",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        me->start_busy(random(2));


        if( query_temp("yidao/mark_steps", me)>11 )
        {
         me->move(__DIR__"caoyuan");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路风尘仆仆之后，蒙古大草原已经近在眼前了......\n"NOR);
         return;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
         me->move(__DIR__"dhunya");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路风尘仆仆之后，断魂崖已经近在眼前了......\n"NOR); 
         return;
        }
        tell_object(me,HIG"你指挥着大军，行进在茫茫的草原上......\n"NOR);  
}

int valid_leave(object me,string dir)
{
       if( dir == "west" )
       addn_temp("yidao/mark_steps", -random(2), me);
       if(  dir == "east" )
       addn_temp("yidao/mark_steps", random(2), me);
       return ::valid_leave(me,dir);
}
