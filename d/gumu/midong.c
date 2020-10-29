// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "河底密洞");
        set("long", @LONG
这里是一座不大的石洞，四周是坚硬的石壁(wall)，看来想要出
去真是难如登天的了。室内只有一床一案，一缕阳光从洞顶的岩缝中
射入，室内光线明亮。墙边有一个青石床 (bed)，与旁边石壁的色泽
有很大不同。透过斜射的阳光，你看到石床对面墙壁上似乎刻着一些
文字和图形。一个宽大的石案上摆着一个石匣(xia)。
LONG
        );
        set("sleep_room", 1);

        set("item_desc",([
                "wall":"\n       只见石壁上刻着“剑动莫名”四个龙飞凤舞的大字。\n
下面有三个持剑捏诀的人像，刻得栩栩如生，每个人姿势都不相同。\n
       旁边还有许多小字,你不妨照着练习(lianxi)一下。\n ",
                "墙壁":"\n       只见石壁上刻着“剑动莫名”四个龙飞凤舞的大字。\n
下面有三个持剑捏诀的人像，刻得栩栩如生，每个人姿势都不相同。\n
       旁边还有许多小字，你不妨照着练习(lianxi)一下。\n ",
                "bed":"\n一个普普通通的石床。\n ",
                "xia":"\n一只石匣，好象是和石案连在一起的，不知道敢不敢打开看看。\n ",
        ]));

        set("mishi_sword",1);
        setup();
}

void init()
{
        add_action("do_lianxi", "lianxi");
        add_action("do_jump", "jump");
        add_action("do_open", "open");
}

int do_lianxi(string arg)
{

        object me=this_player();
        int swordskill=(int)me->query_skill("sword", 1);
        int wumingskill=(int)me->query_skill("wuming-jianfa", 1);
        int exp=(int)query("combat_exp", me);

        if( query("jing", me)<query("max_jing", me)/5 )
                return notify_fail("你已经没有精力练习了！\n");

        if( !query_temp("wuming_onbed", me) )
        {
                message_vision("$N手捏剑诀，照着壁上的图形比划了几次，只觉得一阵口干舌燥。\n", me);
        }
        else
        {
                message_vision("$N手捏剑诀照着壁上图形的姿势比划了几次，脑中灵光一闪似乎领悟到了什么。\n", me);
                if (wumingskill>300)
                        return notify_fail("你照着壁上图形比划了两下，觉得似乎没什么可领悟的了。\n");
                if (exp <= (wumingskill*wumingskill*wumingskill)/10)
                {
                        me->receive_damage("qi", 30);
                        return notify_fail("但是你的经验不够，始终不能从图中领悟到什么。\n");
                }
                if (wumingskill >150 && swordskill>150 )
                {
                        me->improve_skill("wuming-jianfa", (int)(me->query_int()));
                        tell_object(me, "你似乎从中领悟出一些无名剑法方面的窍门。\n");
                }
                else
                {
                        tell_object(me, "你的功夫太低了，还不能领会图形所载的练功法门。\n");
                }
        }
        me->receive_damage("jing", 30);
        return 1;
}

int do_jump(string arg)
{
        object me=this_player();

        if( !arg ||! (arg =="bed" || arg =="up" || arg =="down"))
                return 0;

        if( arg =="up"||arg=="bed")
        {
                if( query_temp("wuming_onbed", me) )
                        return notify_fail("你已经在床上了，再跳就碰到洞顶了。\n");
                set_temp("wuming_onbed", 1, me);
                message_vision("$P轻轻一纵跳上了石床，坐了下来。\n", me);
                tell_object(me, "你只觉得一丝丝凉气从身下传来，顿绝精神一振。\n");
        }

        if( arg =="down"){
                if( !query_temp("wuming_onbed", me) )
                        return notify_fail("你已经在地下了，乱蹦乱跳成何体统？\n");
                delete_temp("wuming_onbed", me);
                message_vision("$P从石床上跳了下来。\n", me);
        }
        return 1;
}

int valid_leave (object me, string dir)
{
        if( query_temp("wuming_onbed", me) )
                return notify_fail("先下床再走，连走路也不会吗？\n");
        return 1;
}

int do_open(string arg)
{
        object me,ob;

        me=this_player();
        if( !arg || arg !="xia")
                return 0;

        if( query("mishi_sword") < 1)
                return notify_fail("你打开石匣。但见里面空空如也。\n");

        addn("mishi_sword", -1);
        message_vision(YEL"$P打开石匣，从里面取出一把"HIR"越女"HIY"朝阳"HIC"剑。\n"NOR, me);
        ob = new("/clone/lonely/yuenv");
        ob->move(me);
        message_vision(HIM"突然凭空卷起一阵狂风,冥冥中响起一个空洞的声音:神技横空,剑赠有缘!去吧.....\n"
                       HIY"呼啸声中,$N的身形已被卷上半空.\n"NOR, me);
        me->move("/d/taohua/lantian");
        return 1;
}

