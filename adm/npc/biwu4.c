#include <ansi.h>
inherit ROOM;

string look_notice();
void create()
{
        set("short", "元老组");
        set("long", @LONG
你眼前是一片绿色的大草坪,草坪的中央是一块大石台。石台的旁边放置着
一块石碑(notice)和几个兵器架(jia)，石碑的后面一面大旗(flag)迎风招展!!!!!!!
大石台上高高悬挂一块大木牌(paizi)，上面写着所有赛程安排情况。
LONG
    );
        set("item_desc", ([ /* sizeof() == 1 */
                "大鼓" : "这是一只牛皮制成的巨鼓，武林人士在华山论剑时敲响(knock)它开始比武。",
                "flag" : " 自 古 英 雄 出 少 年 \n",
                "jia"  : "可以拿(na)的兵器有剑(sword)，刀(blade)，杖(staff)，鞭(whip)，铁锤(hammer)，\n"
                         "暗器(throwing)，棍子(club)。还有衣服(cloth)，护手(hand)，指套(finger)。\n",
                "notice" : (: look_notice :),
        ]));
        
        set("exits", ([ /* sizeof() == 2 */
                "out" : "/d/huashan/houzhiwangyu",
        ]));
        
        set("no_fight", 1);
        set("no_magic", 1);
        set("objects",([
                "/adm/npc/obj/drum4" : 1,
        ]));
        setup();
}

void init()
{
        object me = this_player();
        int age = query("age", me);
        
        /*
        if (! wizardp(me) && age < 40)
        {
                tell_object(me,"大会主持告诉你：你不可以在这个场地比武！请选择你年龄相应的场地！！\n");
                me->move("/d/huashan/houzhiwangyu");
                return;
        }
        */
        
        add_action("get_weapon", ({ "na", "qu", })); 
        add_action("discmds", ({
                "respitate", "exert", "array", "ansuan", "touxi", "persuade", 
                "teach", "exert", "exercise", "study", "learn", "sleep", "kill",
                "steal", "cast", "conjure", "expell", "fight", "hit", "perform", "summon",
                "prcatice", "scribe", "surrender", "sha", "recall", "quit", "exit", "ride", "stab", "team"}));
        call_out("do_recover", 0, me);
}

void do_recover(object me)
{
        if (! me || environment(me) != this_object()) return;
                delete("no_get", me);
        if (! living(me)) me->revive();
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);
        if( query("jingli", me)<query("max_jingli", me) )
                set("jingli",query("max_jingli",  me), me);
        me->clear_weak();
        me->clear_condition();
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        me->start_busy(0);
}

int discmds()
{
        tell_object(this_player(), "现在你还是专心看比武吧！\n");

        return 1;
}

int get_weapon(string arg)
{
        object me, ob;
        object *obs;
        int cloth, sword, blade, staff, whip, hammer, throwing, hand, finger, club;
        int i;
        
        me = this_player();
        
        if (! arg) return notify_fail("你要拿取什么物品？\n");
        
        cloth = sword = blade = staff = whip = hammer = throwing = hand = finger = club = 0;
        
        obs = all_inventory(me);
        for (i = 0; i < sizeof(obs); i++)
        {
                switch (base_name(obs[i])) 
                {
                case "/clone/cloth/cloth":
                        cloth = 1;
                        break;
                case "/clone/weapon/changjian":
                        sword = 1;
                        break;
                case "/clone/weapon/blade":
                        blade = 1;
                        break;
                case "/clone/weapon/zhubang":
                        staff = 1;
                        break;
                case "/clone/weapon/changbian":
                        whip = 1;
                        break;
                case "/clone/weapon/qimeigun":
                        club = 1;
                        break;
                case "/d/city/npc/obj/tieshou":
                        hand = 1;
                        break;
                case "/d/city/npc/obj/zhitao":
                        finger = 1;
                        break;
                case "/clone/weapon/hammer":
                        hammer = 1;
                        break;
                case "/d/tangmen/obj/qinglianzi":
                        if (obs[i]->query_amount() > 1000)
                                throwing = 1;
                        break;
                default:                  
                        break;
                }
        }
                
        switch (arg) 
        {
        case "cloth":
                if (cloth) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/cloth/cloth");
                break;
        case "sword":
                if (sword) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/changjian");
                break;
        case "blade":
                if (blade) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/blade");
                break;
        case "staff":
                if (staff) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/zhubang");
                break;
        case "club":
                if (club) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/qimeigun");
                break;
        case "whip":
                if (whip) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/changbian");
                break;
        case "hammer":
                if (hammer) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/clone/weapon/hammer");
                break;
        case "throwing":
                if (throwing) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/d/tangmen/obj/qinglianzi");
                ob->set_amount(1000);
                break;
        case "finger":
                if (finger) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/d/city/npc/obj/zhitao");
                break;
        case "hand":
                if (hand) return notify_fail("你身上不是已经有了吗？\n");
                ob = new("/d/city/npc/obj/tieshou");
                break;
        default:  
                return notify_fail("你要拿取什么物品？\n"); 
                break;
        }
        
        ob->move(me, 1);
        
        tell_object(me,"你从架上拿下了一"+query("unit", ob)+ob->name()+"。\n");
        return 1;
}
        
string look_notice()
{
        object who;
        string *name_list;
        string file;
        int i, j = 0, k;
        
        who = this_player();
        file = read_file("/log/static/lunjian4");
        if (! file)
                return "目前没有任何比武记录。\n";
        name_list = explode(file, "\n");
        for (i = 0; i < sizeof(name_list); i++) 
        {
                if (name_list[i] == "seperator") 
                {
                        j++;
                        k = 0;
                        printf("\n第" + chinese_number(j) + "届(元老组)华山论剑结果：\n");
                        continue;
                }
                k++;
                printf(GRN "第" + chinese_number(k) + "名：%-50s\n" NOR, name_list[i]);
        }
        return "\n";
}
int valid_leave(object me, string dir) 
{
        delete_temp("flag_hslj", me);
        return ::valid_leave(me, dir);
}
