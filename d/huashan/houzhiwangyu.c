#include <ansi.h>
inherit ROOM;

void message_competition(string msg);
void create()
{
        set("short", "猴子望月");
        set("long", @LONG
此处原是一仞高耸入云的峭壁，不知何年由人从峭壁的半腰硬是
开出一条栈道来，栈道旁有一粗十余丈的擎天石柱，石柱顶生一松，
松旁有一天生奇石，宛如翘首望月的猴子。 
LONG );
        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
/*
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
*/
        ]));

        set("outdoors", "huashan" );

        set("no_fight", 1);
        setup();
}

void init()
{
        if ((wiz_level(this_player()) >= 5) || query("id", this_player())=="lazy cat")
        {
                add_action("do_open", "open");
                add_action("do_close", "close");
        }
}

int do_open()
{
        object me = this_player();

        if (query("exits/up"))
                return notify_fail("门已经是开着的了。\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
//                      "4" : "/adm/npc/biwu4", 
        ]));

        message_vision(HIY "$N" HIY "轻轻一推，将通向武林大会会场的"
                       "大门开启了。\n" NOR, me);

        shout(HIY "【华山论剑】" NOR + WHT + me->name() + WHT "[" +
              query("id", me)+WHT"]开启了华山绝顶的武林大会会场。\n"NOR);

        return 1;
}

int do_close()
{
        object me = this_player();

        if (! query("exits/up"))
                return notify_fail("门已经是关着的了。\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
        ]));
        message_vision(WHT "$N" WHT "顺手一带，将通向武林大会会场的"
                       "大门关上了。\n" NOR, me);
        return 1;
}

void message_competition(string msg)
{
        CHANNEL_D->channel_broadcast("rumor", msg);
}

int valid_leave(object me, string dir)
{
        int i;
        object *inv;
        int age=query("age", me);

                if (!playerp(me) && dir != "southdown") return -1;

        if (dir == "southdown" || dir == "up")
                return 1;
                
//        set_temp("flag_hslj", 1, me);
                
        inv = deep_inventory(me);

        if( dir != "northup" )
        for(i=sizeof(inv)-1; i>=0; i--)
        {
        if (inv[i]->is_xpzhu()) continue;

                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");

                if (! wizardp(me) &&
                    inv[i]->is_cruise_ob())
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    inv[i]->is_item_make())
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    query("weapon_prop", inv[i]) )
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    query("armor_prop", inv[i]) )
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");
        }

        if (wizardp(me)) {
                return 1;
        }
        
                if (dir == "1" && query("level", me) >= 20 && query("level", me) <= 100) {
                        message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的1号比武场。");
        set_temp("flag_hslj", 1, me);
        BUFF_D->debuff(me, "powerofsun", "bless");
        BUFF_D->debuff(me, "powerofmoon", "bless");
        BUFF_D->debuff(me, "powerofstar", "bless");
                                return 1;
                }
                if (dir == "2" && query("level", me) >= 101 && query("level", me) <= 200)  {
                        message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的2号比武场。");
        set_temp("flag_hslj", 2, me);
        BUFF_D->debuff(me, "powerofsun", "bless");
        BUFF_D->debuff(me, "powerofmoon", "bless");
        BUFF_D->debuff(me, "powerofstar", "bless");
                                return 1;
                }
                if (dir == "3" && query("level", me) >= 201)  {
                        message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的3号比武场。");
        set_temp("flag_hslj", 3, me);
        BUFF_D->debuff(me, "powerofsun", "bless");
        BUFF_D->debuff(me, "powerofmoon", "bless");
        BUFF_D->debuff(me, "powerofstar", "bless");
                                return 1;
                }
                if (dir == "4" && query("level", me) >= 20) {
                        message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的4号比武场。");
        set_temp("flag_hslj", 4, me);
        BUFF_D->debuff(me, "powerofsun", "bless");
        BUFF_D->debuff(me, "powerofmoon", "bless");
        BUFF_D->debuff(me, "powerofstar", "bless");
                                return 1;
                }

        if (dir == "northup")
        {
                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");
                message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的论剑比武场。");
        set_temp("flag_hslj", 5, me);
                return 1;
        }
        
        return notify_fail("你不可以到那边比武！！\n");
}

