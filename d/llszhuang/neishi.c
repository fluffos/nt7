#include <ansi.h>
inherit ROOM;
string look_book();
void create()
{
        set("short","栖霞馆");
        set("long",
"这里是日常起居的地方，收拾得一尘不染，而且颇为雅致，据说这里\n"
"的庄主颇爱习武，看看墙上挂着的毒药囊和刀枪就可以知道。靠窗的地方\n"
"是一个梳妆台，镜子前面是一本翻开的书(Book)。还有一个奇形怪状的轮\n"
"盘放在旁边，也许是什么古怪机关。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"hall",
        ]));
        set("seed1",random(10)+1);
        set("seed2",random(20)+21);
        set("seed3",random(50)+51);
        set("seed4",random(100)+101);

      set("item_desc", ([
                "book": (: look_book :),
        ]) );

        setup();
}

int init()
{
        add_action("do_turn","turn");
}

string look_book()
{
        string result;
        object me;
        int puzzle;

        me = this_player();
        result = "\n这本书上没有什么值得注意的东西。\n";
        if( puzzle=query_temp("marks/xanadu_hall2", me) )
        {
                set_temp("marks/xanadu_hall3", 1, me);
              result += "就在你失望地要放下书的时候，里面掉出来一张字条，上面写到: \n"
                          "拨动轮盘就有一道门可以进去。\n";
                result += "对了，还有，轮盘的数字嘛，要考考你...\n";
                result += "这个数，它除"+query("seed1")+"余"+puzzle%query("seed1")+"，";
                result += "它除"+query("seed2")+"余"+puzzle%query("seed2")+"，";
                result += "它除"+query("seed3")+"余"+puzzle%query("seed3")+"，";
                result += "它除"+query("seed4")+"余"+puzzle%query("seed4")+"\n";
                result += "然后试一下(turn)你猜到的数字，看看有什么发现。\n";
        }
        return result;
}

int do_turn(string arg)
{
        object me;
        int answer,puzzle;

        me = this_player();
        if(!arg)
                return notify_fail("你要把轮盘转到哪一个数字上？\n");
        if( query("neili", me)<500 )
                return notify_fail("你的内力不够，拨不动轮盘。\n");
            if( !(answer = (int)arg) || !(query_temp("marks/xanadu_hall3", me)) ) 
              return notify_fail("你瞎转什么？\n");
        addn("force", -150, me);
        message_vision("$N把轮盘拨到了"+arg+"的位置\n",me);
        puzzle=query_temp("marks/xanadu_hall2", me);
        if( ("X"+puzzle+"X") == ("X"+answer+"X") )
        {
                write("一阵机关之声响过之后，你来到了一个新的地方。\n");
                delete_temp("marks/xanadu_hall2", me);
                delete_temp("marks/xanadu_hall3", me);
                me->move(__DIR__"lou0");
                tell_room(this_object(),"墙上突然开了一道门，"+query("name", me )
+"毫不犹豫地走了进去。\n");
        }
        else
                message_vision("可是什么都没有发生。\n",me);
        return 1;
}
