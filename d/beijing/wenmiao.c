#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "文庙");
        set("long", @LONG
这里是文庙正殿，内有孔夫子像。历代皇帝都懂得利用儒教思想
来巩固自己的江山社稷，当朝皇帝自然也不例外。不论何人到此，都
毕恭毕敬地上香礼拜。孔夫子讲究的是人的悟性，要成为一位扬名天
下的大侠，光靠武力往往不能做到，还需要有足够的智慧。不少江湖
中流名千古的神话人物，在初入江湖时，都曾经在这里发下誓言，虔
诚的膜拜(mobai)。 而新玩家也可以在这里许愿(xuyuan)，明确一下
自己的性格，踏上漫漫江湖路。
LONG );

        set("no_fight",1);
        set("no_drift", 1);
        set("valid_startroom","1");
        set("exits", ([
                "south" : "/d/beijing/dong_3",
        ]));

	set("coor/x", -2780);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_mobai","mobai");
        add_action("do_chouqian","chouqian");
        add_action("do_xuyuan","xuyuan");
}

int do_mobai(string arg){
        int i;
        int gift;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        return notify_fail("你还是去扬州戚长发那里购买天赋丹洗点吧，这里再膜拜也没有用了。\n");
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->is_busy()) return notify_fail("你正忙着呢，膜拜还要三心二意？\n");
        if( query("can_not_change", me) )
                return notify_fail("你正对着孔子像双膝跪下，无比虔诚的膜拜这位华夏圣人，良久才起身。\n");
        write(HIC "你对着孔子像毕恭毕敬的跪了下去，双手合十开始膜拜。\n" NOR, me);
        gift = query("int", me) + query("con", me) + query("str", me) + query("dex", me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpint = 23;
        points = gift - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: 
                        if (tmpstr < 30) tmpstr++;
                        else i--; 
                        break;
                case 1: 
                        if (tmpint < 30) tmpint++;
                        else i--;
                        break;
                case 2: 
                        if (tmpcon < 30) tmpcon++;
                        else i--;
                        break;
                case 3:
                        if (tmpdex < 30) tmpdex++;
                        else i--;
                        break;
                }
        }
        my = me->query_entire_dbase();
        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);
        write(HIC "突然一阵深沉的声音在你心头响起：“这是我给你的天资！”\n" NOR, me);
        write(sprintf(HIY "\n你只感觉身体里一道圣气缓缓流转，你的秉性变化了：\n"
                          "膂力：【 " HIG "%d" HIY " 】 "
                          "悟性：【 " HIG "%d" HIY " 】 "
                          "根骨：【 " HIG "%d" HIY " 】 "
                          "身法：【 " HIG "%d" HIY " 】\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        me->start_busy(1);
        return 1;
}

int do_chouqian(string arg)
{
        object me;
        string *character = ({
                "心狠手辣",
                "光明磊落",
                "狡黠多变",
                "阴险奸诈",
         });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query_temp("last_chouqian_time", me)<1 )
                return notify_fail("这么频繁的抽签干嘛？心不诚则签不灵，过半个小时再来吧。\n");

        write(HIC "你虔诚的抽了一根签，闭目祈祷了一阵，才睁开眼睛看签上所书文字。\n" NOR, me);
        write(HIC "签上写着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set_temp("last_chouqian_time", time(), me);
        //if( query("can_not_change", me))return 1;
        set("character", character[random(sizeof(character))], me);
        write(sprintf(HIY"\n你隐隐听到一阵深沉的声音：朝『%s』的方向发展吧。\n"NOR,query("character", me)));
        return 1;
}

int do_xuyuan(string arg)
{
        object me;
        string *character = ({
                "心狠手辣",
                "光明磊落",
                "狡黠多变",
                "阴险奸诈",
         });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query_temp("last_chouqian_time", me)<1 )
                return notify_fail("这么频繁的抽签干嘛？心不诚则签不灵，过半个小时再来吧。\n");

        write(HIC "你虔诚的抽了一根签，闭目祈祷了一阵，才睁开眼睛看签上所书文字。\n" NOR, me);
        write(HIC "签上写着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set_temp("last_chouqian_time", time(), me);
        //if( query("can_not_change", me))return 1;
        if( member_array(arg, character) == -1 )
                arg = character[random(sizeof(character))];
        set("character", arg, me);
        write(sprintf(HIY"\n你隐隐听到一阵深沉的声音：朝『%s』的方向发展吧。\n"NOR,query("character", me)));
        return 1;
}
