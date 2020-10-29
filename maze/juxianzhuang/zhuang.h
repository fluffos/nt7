
#include <ansi.h>
void init()
{
        object me, hero, ob, room;
        object azhu;

        me = this_player();
        room = environment(me);
        hero = present("qiao feng", room);
        azhu = present("a zhu", room);
        if( objectp(hero) && objectp(azhu) && me->query_temp("juxianzhuang_step") == 13 )
        {

                if( room->query("short") == "游府正厅" )
                {
                        tell_object(me, HIW "乔峰见你进来便对你说道：我一会儿便要和天下英雄喝酒断义。你是超然物外的英雄，聚贤庄的人应该不会为难你的。\n"
                                            "念我们旧日的情谊，请你千万照顾阿朱姑娘周全。\n"
                                            "以阿朱的伤势，难以坚持太久，只有薛神医才救得了她。切记，切记。\n" NOR);
                        message_vision(HIW "$N端起一碗酒来，说道：“这里众家英雄，多有往日乔峰旧交，今日既有见疑之意，咱们干杯绝交。\n"
                                           "哪一位朋友要杀乔某的，先来对饮一碗，从此而后，往日交情一笔勾消。我杀你不是忘恩，你杀我不算负义。\n"
                                           "天下英雄，俱为证见。\n" NOR,
                                           hero, me);
                        message_vision(HIW "断义酒喝罢，$N跃入院子，大声喝道：“哪一个先来决一死战！”，顿时群雄蜂拥而上。\n" NOR, hero, me);
                        azhu->set_leader(me);
                        hero->command("go east");
                        room = environment(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/youji");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/youju");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                if( room->query("short") == "演武场" )
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xu");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/shanzheng");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                if( room->query("short") == "游府后院" )
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xuan-nan");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xuan-ji");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
        }
}
