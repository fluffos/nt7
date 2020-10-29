// Room: /yuelaoci.c
#define QIUQIAN "/d/hangzhou/qiuqian"

#include <ansi.h>

#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
        set("short", "月老祠");
        set("long", @LONG
月老是神话中掌管姻缘的仙人，传说他有红线，若把它系在男女
朋方的脚上，虽仇人或相隔千里，终会结成姻缘。月老祠一间小院、
三五瓦屋。正屋中央的神龛里坐着月下老人：红风帽红披肩，鹤发童
颜，笑容满面。神龛前面照例是供桌、香炉、烛台、签筒，当然，蒲
团也是少不了的。两旁一副黑漆的小对联：愿天下有情人，都成了眷
属；是前生注定事，莫错过姻缘。令人拍案叫绝。你可以在这里求签
（qiuqian）问一下姻缘情事。
LONG );
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room","1");

        set("exits", ([
                "south" : "/d/hangzhou/yuanyuan-tai",

        ]));
	set("coor/x", 770);
	set("coor/y", -1960);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_qiuqian","qiuqian");
}

int do_qiuqian(string arg)
{
            object me;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query("last_qiuqian_time", me)<600 )
                return notify_fail("这么频繁的求签干嘛？心不诚则签不灵，过十分钟再来吧。\n");

        write(HIC "
你虔诚地向月老像拜了几拜，口中念念有词：“月老月老，赐给我好姻缘吧！”
你闭着眼擎了支签，又祈祷了一会，这才睁开眼睛看签文。\n
" NOR, me);
        write(HIC "签上写着：" + QIUQIAN->query_qiuqian() + "。\n" NOR, me);
        set("last_qiuqian_time", time(), me);
        return 1;
}