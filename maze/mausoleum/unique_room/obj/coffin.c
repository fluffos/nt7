#include <ansi.h>
inherit ITEM;

int generate_taoist;
void set_generate_taoist(int i)
{
        generate_taoist = i;
}

int query_generate_taoist()
{
        return generate_taoist;
}

void create()
{
        set_name("棺材", ({"coffin"}) );
        set_weight(3000);
        set("no_get", 1);
        set("unit", "具");
        set("long", "一具汉白玉做的石棺，上面还有一个奇形怪状的轮盘，也许是什么古怪机关。");
        set("value", 2000);
        setup();
}

void init()
{
        add_action("do_push","push");
        add_action("do_turn","turn");
}

int do_push(string arg)
{
        if( !arg || (arg!="coffin" &&  arg!="棺材") )
                return notify_fail("你要推什么？\n");

        tell_object(this_player(), "棺材似乎只有拨转(turn)轮盘才能开启机关打开。\n");
        return 1;
}

int do_turn(string arg)
{
        object taoist;
        object me, mazeobj;
        int answer,puzzle;

        me = this_player();
        if( !arg )
                return notify_fail("你要把轮盘转到哪一个数字上？\n");
        if( query("neili", me) < 5000 )
                return notify_fail("你的内力不够，拨不动轮盘。\n");
        mazeobj = FUBEN_D->query_maze_mainobj(this_object());
        if( !(answer = (int)arg) || sizeof(query("quest/password", mazeobj)) < 9 )
                return notify_fail("你瞎转什么？\n");
        puzzle  = query("quest/password/1", mazeobj);
        puzzle += query("quest/password/2", mazeobj) * 10;
        puzzle += query("quest/password/3", mazeobj) * 100;
        puzzle += query("quest/password/4", mazeobj) * 1000;
        puzzle += query("quest/password/5", mazeobj) * 10000;
        puzzle += query("quest/password/6", mazeobj) * 100000;
        puzzle += query("quest/password/7", mazeobj) * 1000000;
        puzzle += query("quest/password/8", mazeobj) * 10000000;
        puzzle += query("quest/password/9", mazeobj) * 100000000;
        me->add("neili",-1500);
        message_vision("$N把轮盘拨到了"+arg+"的位置\n",me);
        if( ("X"+puzzle+"X") == ("X"+answer+"X") ) {
                if( query_generate_taoist() ) {
                        tell_room(this_object(), "一阵机关之声响过之后棺材打开了，但是里面什么都没有。\n");
                        return 1;
                }
                tell_room(this_object(), "一阵机关之声响过之后，石棺开始慢慢开启。\n");
                message_vision(@LONG
棺中躺了一个头戴珍珠玄冠，身着黑色龙袍的俊秀王者，面如冠玉，神态安详平和，
宛然若生，似乎只是在沉睡之中。左手横于胸前，托着一个三寸来长、形如猛虎的五
色石印，绚光闪耀。右手垂膝，紧握着一根六尺来长的盘龙青铜旗杆，黑色幡布横铺
在他的腹部，赫然是河图纹案。棺盖打开之后，尸体紧闭的双眼突然睁开，双目之中
精光暴射，随即从棺中一跃而出，可能是在棺中躺了千年的缘故，他的手臂腿脚都不
十分灵便，但他力大无穷，直上直下，手脚挥舞着向你攻来。跃出石棺之后，他的皮
肉急速萎缩焦枯，刹那之间便化为一具白骨骷髅！
LONG, me);
                taoist = new("/maze/mausoleum/npc/king");
                taoist->move(environment(me));
                set_generate_taoist(1);
        } else
                message_vision("可是什么都没有发生。\n",me);
        return 1;
}

