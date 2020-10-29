// /d/mingjiao/bhd/congling1.c
// Jay 4/3/97 -qingyun
// Modify By River@SJ 99.06
#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_tree();
void create()
{ 
        set("short",HIG"丛林"NOR);
        set("long", @LONG
这是一片厚厚的丛林。几十丈高的树木(tree)簇在一块，密实的
枝叶象一蓬蓬巨伞恒伸向天空，把阳光遮得丝毫也无。由于丛林历时
年代很久，又罕有人至，所以动植物种类很多，飞禽走兽应有尽有。
偶尔会有吃肉兽出来伤人。你一走进这这觉得阴阴森林的。
LONG );
        set("exits", ([
                "south" : __DIR__"cling",
        ]));    
        set("item_desc", ([
                "tree" : (: look_tree :),
          ]));
        set("objects",([
                "/d/mingjiao/npc/xiong"  :  2,
        ]));
        set("tree_count", 2);
        set("outdoors","冰火岛");
        setup();
}

void reset()
{
        set("tree_count", 2);
        ::reset();
}

void init()
{
        add_action("do_chop","chop");
        add_action("do_chop","砍");
}

int do_chop(string arg)
{
        object me, weapon;
        me = this_player();
        weapon = me->query_temp("weapon");
        if( arg=="tree" || arg=="Tree" || arg=="树木" ) {
             if(me->is_busy()) return notify_fail("你正忙着呢。\n");
             if(query("tree_count") < 1) return notify_fail("剩下的树木都太大了，你还是再找找吧。\n");
             me->start_busy(1);
             if(!weapon){
                     message_vision("\n$N运功吐气，一掌打在那千年老树坚实的树干上，痛得$P眼泪直往下掉！\n\n",me);
                     me->set_temp("last_damage_from", "被自己的反震力打");
                     me->receive_wound("qi", 50);
                     me->receive_damage("qi", 50);
                     EMOTE_D->do_emote(me,"nocry");
                     return 1;
             }
             else if(weapon->query("flag")!=4){
                     message_vision("\n$N拿起$n，往树上一阵乱敲。\n"+
                                    "结果梆的一声掉下根枯树枝来，正好打在$P头上，顿时起了个大包！\n",me, weapon);
                     me->set_temp("last_damage_from", "被树枝压");
                     EMOTE_D->do_emote(me,"pain");
                     EMOTE_D->do_emote(me,"cry");
                     me->receive_wound("qi", 50);
                     me->receive_damage("qi", 50);
                     return 1;
             }
             else{
                     message_vision("\n$N操起$n，往树干上砍啊，砍啊，砍啊。。。\n",me, weapon);
                     if(random(100) > 90){
                          message_vision("\n只听哗啦一声，这棵树木总算被$N砍倒了。\n",me);
                          new("/d/mingjiao/obj/tree")->move(this_object());
                          add("tree_count", -1);
                     }
                     me->receive_damage("jing", random(20)+10);
                     me->improve_skill(weapon->query("skill_type"), random(me->query("str")));
                     return 1;
             }
        }
}    
   
string look_tree()
{
       return
       " 
                            m
           *               m*m
         *****            m***m
        ***|*/*          m*****m
       ****|****        mm*****mm
         **Y**          mm**Y**mm
^^    ^^   |   ^^  ^^      *|*     ^^   ^^
------------------------------------------

这里的树木高大茂密，树干结实，很适合制造船舶。\n";
}

