#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "佛庙");
        set("long", @LONG
这里是佛庙正殿，内有佛祖金身。虽然与少林、峨嵋等佛教盛地
相比，这个庙又小又简陋，但是据传这里的释迦牟尼金身像乃当年鉴
真从天竺所带来，无比灵异，因此这里常年香火鼎盛。佛门讲究一个
缘字，重视人的先天根骨，不少玩家为了让自己拥有超常的根骨，经
常来这里顶礼膜拜(mobai)。 新玩家也可以在这里抽签(chouqian)，
明确一下自己的性格，踏上漫漫江湖路。
LONG );

       set("no_fight",1);
        set("no_drift", 1);
        set("valid_startroom","1");
        set("exits", ([
                "north" : __DIR__"shuduroad1",
        ]));

        set("coor/x", -15210);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
/*
void init()
{
        add_action("do_mobai","mobai");
        add_action("do_chouqian","chouqian");
}

int do_mobai(string arg){
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->is_busy()) return notify_fail("你正忙着呢，膜拜还要三心二意？\n");
        if( query("can_not_change", me) )
                return notify_fail("你正对着佛祖金像双膝跪下，无比虔诚的顶礼膜拜，良久才起身。\n");
        write(HIC "你对着佛祖金像毕恭毕敬的跪了下去，双手合十开始膜拜。\n" NOR, me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpcon = 23;
        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
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
        write(HIC "突然一阵慈祥的声音在你心头响起：“这是我赐予你的天资！”\n" NOR, me);
        write(sprintf(HIY "\n一道佛光笼罩你全身，你的秉性变化了：\n"
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

        if( time()-query("last_chouqian_time", me)<1800 )
                return notify_fail("这么频繁的抽签干嘛？心不诚则签不灵，过半个小时再来吧。\n");

        write(HIC "你虔诚的抽了一根签，闭目祈祷了一阵，才睁开眼睛看签上所书文字。\n" NOR, me);
        write(HIC "签上写着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set("last_chouqian_time", time(), me);
        if( query("can_not_change", me))return 1;
        set("character", character[random(sizeof(character))], me);
        write(sprintf(HIY"\n你隐隐听到一阵慈祥的声音：朝『%s』的方向发展吧。\n"NOR,query("character", me)));
        return 1;
}
*/