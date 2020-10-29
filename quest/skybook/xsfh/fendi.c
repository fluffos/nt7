inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",HIB"墓地"NOR);
        set("long",@LONG
走到这里越发感到荒凉，黄叶随风乱舞，四处弥漫着朽木腐烂的气味。没
膝的杂草中有一座土坟，墓碑(bei) 上落满了尘土，不仔细看，很难辩出上面
写些什么。墓前并无纸灰，看起来好久没有人来祭拜了。
LONG
        );
        set("no_fight", 1);
        set("no_get_from", 1);
        set("no_sleep_room", 1);
        set("dao_count",1);
        set("exits", ([
               "south" : __DIR__"shulin6",
        ]) );
        set("quest",1);

        set("objects",([
            __DIR__"npc/hu-fei" : 1,
        ]));

        set("item_desc", ([
                "bei"||"墓碑"||"碑":@LONG
             ________
            /        \
           /          \
          |        辽  |
          |            |
          |        东  |
          |     胡     |
          |     一 大  |
          |     刀     |
          |     夫 侠  |
          | 苗  妇     |
          | 人         |
          | 凤  之     |
          | 立         |
          |     墓     |
          |            |
LONG
        ]) );

        set("coor/x",70);
        set("coor/y",80);
        set("coor/z",0);
        setup();
}

void init()
{
        add_action("do_wa", "wa");
}

int do_wa(string arg)
{
        object dao, me, ob;
        me = this_player();

        if( ! arg || arg != "di")
                return notify_fail("你要挖什麽？\n");

        if( ob = present("hu fei",environment(me)) &&!me->query("quest/雪山飞狐/复仇篇/over")) {
//              message_vision("$N用一种异样的眼神看着$n。\n", ob,me);
                return notify_fail(CYN"胡斐喝道：休要打扰我爹娘的清静！\n"NOR"你不敢再有动作！\n");
        }

        if ((int)me->query("jingli") < 500)
                return notify_fail("你的精力不够做这件事！\n");

        if(random(10)!=6) {
                me->add("jingli",-200);
                return notify_fail("你看准了墓后三尺之处，运劲于指，伸手挖土。\n");
        }

        dao = new(__DIR__"obj/lengyue-dao");

        if(!clonep(dao)){
                tell_room(environment(me), me->name() + "挖了半天，只弄了一手泥。\n", ({ me }));
                return notify_fail("你挖了半天，只弄了一手泥。\n");
        }

        if(clonep(dao) && dao->violate_unique()){
                destruct(dao);
                tell_room(environment(me), me->name() + "挖了半天，只弄了一手泥。\n", ({ me }));
                return notify_fail("你挖了半天，只弄了一手泥。\n");
        }
        message_vision("挖地三尺，$N感到双手手指同时碰到一件冰冷坚硬之物，再向两旁摸索，是一柄带鞘的单刀。\n"+
                       "$N抓住刀柄轻轻把单刀从土中抽出，刀刃抽出寸许，毫无生锈。\n",me);
        me->add("jingli", -500);
        dao->move(me);
        return 1;
}
