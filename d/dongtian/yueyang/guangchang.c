// This program is a part of NITAN MudLIB
// redl 2013/10
#include <ansi.h>
inherit ROOM;

#define XIANG_MAXLIFE 600
#define THUNDER_DAMAGE_PERCENT 100 //%
#define YANXI_NUM 5600
#define ATTACKER_LV 10


int do_clear();
int do_expel_allusers();
void add_ownlist(object me);
int add_qy2(int addnum);
int query_dt_qy();
int add_qy();

#define SHORTZHEN ({HIB + "幻阵" + NOR, HIM + "迷阵" + NOR, HIG + "陷阵" + NOR, HIR + "杀阵" + NOR, HIY + "绝阵" + NOR, BRED + HIC + "劫阵" + NOR})

mapping REQ_ITEMS2 =     ([     //升级研究练习专用
                "符文11号" :    "/clone/tessera/rune11",
                "符文12号" :    "/clone/tessera/rune12",
                "符文13号" :    "/clone/tessera/rune13",
                "符文14号" :    "/clone/tessera/rune14",
                "符文15号" :    "/clone/tessera/rune15",
                "符文16号" :    "/clone/tessera/rune16",
                "符文17号" :    "/clone/tessera/rune17",
                "符文18号" :    "/clone/tessera/rune18",
                "符文19号" :    "/clone/tessera/rune19",
                "符文20号" :    "/clone/tessera/rune20",
        ]);

mapping *REQ_ITEMS = ({
        ([
                "千两金票" :    "/clone/money/thousand-gold",
                "无名小铜人" :  "/clone/tongren/tongren1",
                "无名大铜人" :  "/clone/tongren/tongren2",
                "玉清丸" :              "/clone/medicine/yuqingwan",
                "稀世水晶钻" :  "/clone/tessera/fdiamond",
                "稀世翡翠绿" :  "/clone/tessera/femerald",
                "稀世蓝宝石" :  "/clone/tessera/fsapphire",
                "稀世红宝石" :  "/clone/tessera/fruby",
                "稀世黄宝石" :  "/clone/tessera/ftopaz",
                "符文1号" :     "/clone/tessera/rune01",
                "符文2号" :     "/clone/tessera/rune02",
                "符文3号" :     "/clone/tessera/rune03",
                "符文4号" :     "/clone/tessera/rune04",
                "符文5号" :     "/clone/tessera/rune05",
                "符文6号" :     "/clone/tessera/rune06",
                "符文7号" :     "/clone/tessera/rune07",
                "符文8号" :     "/clone/tessera/rune08",
                "符文9号" :     "/clone/tessera/rune09",
                "符文10号" :    "/clone/tessera/rune10"
        ]),
         ([
                "神之水晶钻" :  "/clone/tessera/mdiamond",
                "神之翡翠绿" :  "/clone/tessera/memerald",
                "神之蓝宝石" :  "/clone/tessera/msapphire",
                "神之红宝石" :  "/clone/tessera/mruby",
                "神之黄宝石" :  "/clone/tessera/mtopaz",
                "符文11号" :    "/clone/tessera/rune11",
                "符文12号" :    "/clone/tessera/rune12",
                "符文13号" :    "/clone/tessera/rune13",
                "符文14号" :    "/clone/tessera/rune14",
                "符文15号" :    "/clone/tessera/rune15",
                "符文16号" :    "/clone/tessera/rune16",
                "符文17号" :    "/clone/tessera/rune17",
                "符文18号" :    "/clone/tessera/rune18",
                "符文19号" :    "/clone/tessera/rune19",
                "符文20号" :    "/clone/tessera/rune20"
        ]),
         ([
                "符文21号" :    "/clone/tessera/rune21",
                "符文22号" :    "/clone/tessera/rune22",
                "符文23号" :    "/clone/tessera/rune23",
                "符文24号" :    "/clone/tessera/rune24",
                "符文25号" :    "/clone/tessera/rune25",
                "史诗护甲" :    "/inherit/template/armor/armor",
                "史诗靴子" :    "/inherit/template/armor/boots",
                "史诗战衣" :    "/inherit/template/armor/cloth",
                "史诗指套" :    "/inherit/template/armor/finger",
                "史诗掌套" :    "/inherit/template/armor/hands",
                "史诗头盔" :    "/inherit/template/armor/head",
                "史诗披风" :    "/inherit/template/armor/surcoat",
                "史诗腰带" :    "/inherit/template/armor/waist",
                "史诗护腕" :    "/inherit/template/armor/wrists",
//              "史诗斧" :              "/inherit/template/weapon/axe",
                "史诗刀" :              "/inherit/template/weapon/blade",
                "史诗棍" :              "/inherit/template/weapon/club",
                "史诗锤" :              "/inherit/template/weapon/hammer",
                "史诗杖" :              "/inherit/template/weapon/staff",
                "史诗剑" :              "/inherit/template/weapon/sword",
                //"史诗暗器" :  "/inherit/template/weapon/throwing",
                "史诗鞭" :              "/inherit/template/weapon/whip",
                "史诗萧" :              "/inherit/template/weapon/xsword"
        ]),
         ([
                "符文26号" :    "/clone/tessera/rune26",
                "符文27号" :    "/clone/tessera/rune27",
                "符文28号" :    "/clone/tessera/rune28",
                "符文29号" :    "/clone/tessera/rune29",
                "符文30号" :    "/clone/tessera/rune30",
                "传说护甲" :    "/inherit/template/armor/armor",
                "传说靴子" :    "/inherit/template/armor/boots",
                "传说战衣" :    "/inherit/template/armor/cloth",
                "传说指套" :    "/inherit/template/armor/finger",
                "传说掌套" :    "/inherit/template/armor/hands",
                "传说头盔" :    "/inherit/template/armor/head",
                "传说披风" :    "/inherit/template/armor/surcoat",
                "传说腰带" :    "/inherit/template/armor/waist",
                "传说护腕" :    "/inherit/template/armor/wrists",
//              "传说斧" :              "/inherit/template/weapon/axe",
                "传说刀" :              "/inherit/template/weapon/blade",
                "传说棍" :              "/inherit/template/weapon/club",
                "传说锤" :              "/inherit/template/weapon/hammer",
                "传说杖" :              "/inherit/template/weapon/staff",
                "传说剑" :              "/inherit/template/weapon/sword",
                //"传说暗器" :  "/inherit/template/weapon/throwing",
                "传说鞭" :              "/inherit/template/weapon/whip",
                "传说萧" :              "/inherit/template/weapon/xsword"
        ]),
         ([
                "符文31号" :    "/clone/tessera/rune31",
                "符文32号" :    "/clone/tessera/rune32",
                "符文33号" :    "/clone/tessera/rune33",
                "神器护甲" :    "/inherit/template/armor/armor",
                "神器靴子" :    "/inherit/template/armor/boots",
                "神器战衣" :    "/inherit/template/armor/cloth",
                "神器指套" :    "/inherit/template/armor/finger",
                "神器掌套" :    "/inherit/template/armor/hands",
                "神器头盔" :    "/inherit/template/armor/head",
                "神器披风" :    "/inherit/template/armor/surcoat",
                "神器腰带" :    "/inherit/template/armor/waist",
                "神器护腕" :    "/inherit/template/armor/wrists",
//              "神器斧" :              "/inherit/template/weapon/axe",
                "神器刀" :              "/inherit/template/weapon/blade",
                "神器棍" :              "/inherit/template/weapon/club",
                "神器锤" :              "/inherit/template/weapon/hammer",
                "神器杖" :              "/inherit/template/weapon/staff",
                "神器剑" :              "/inherit/template/weapon/sword",
                //"神器暗器" :  "/inherit/template/weapon/throwing",
                "神器鞭" :              "/inherit/template/weapon/whip",
                "神器萧" :              "/inherit/template/weapon/xsword"
        ])
        });


int clean_up() { return 1;}

string load_name()
{
    if (file_size(__DIR__"name.o")>0) {return replace_string(read_file(__DIR__"name.o"), "\n", "");}
        return "无名";
}

int save_name(string arg)
{
        if (!arg || arg=="")
                return notify_fail(NOR"没有arg来指定洞天名！\n"NOR);
        write_file(__DIR__"name.o", arg, 1);
        reload_object(this_object());
        return 1;
}

string dtname = load_name();

int owner_level(object me)
{
        int i;
        string *owns, *broids;
        mapping bro;

        if (!query("flag_init")) reload_object(this_object());

        owns = query("owners");
        if (owns && !undefinedp(owns) && member_array(query("id", me), owns) > -1)
                return 2;//攻占洞天时的队伍成员和当时的伴侣为主人
        if (owns && !undefinedp(owns) && sizeof(owns)>0 && mapp(bro=query("brothers", me)) && sizeof(bro)>0 ) {
                                broids = keys(bro);
                        for( i = 0; i < sizeof(broids); i++ ) {
                                if (member_array(broids[i], owns) > -1) {
                                        return 1;//主人的结义
                                }
                                }

        }

        return 0;
}

int halt_attacking(object me)
{
        write(NOR "你停止了对阵图的攻击。\n" NOR);
        delete("attacker_player");
        me->set_short_desc(0);
        return 1;
}

int halt_attacking2()
{
        delete("attacker_player");
        return 1;
}

int attacking(object me)
{
        object ob;
        object *obs, *t, tob;
        string coupid, *owns = ({});
        int ti1, ti2, n = 0, i, plv, npci = random(2) + 2;

        if (query("xiang_life") < 2 && objectp(me) && !playerp(me)) {//先玩家1点攻破
                CHANNEL_D->channel_broadcast("rumor", NOR + MAG + "据说" + dtname + "洞天被神秘人攻破。\n" NOR);
                message_vision(append_color(NOR YEL "魔像阵图已经被$N" NOR YEL "攻破，天旋地转之中洞天一阵扭曲。\n" NOR, YEL), me);
                do_clear();
                set("protect_time", time() + 14400);//比玩家多2小时保护
                delete("attacker_player");
                do_expel_allusers();
                return 1;
        }

        if (environment(me)!=this_object()) {
                tell_object(me, CYN "你跑到哪里去了？\n" + NOR);
        delete("attacker_player");
                me->set_short_desc(0);
                me->command("halt");
                return 1;
        }
        if (me->is_fighting()) {
                tell_object(me, CYN "你被攻击了！\n" + NOR);
        delete("attacker_player");
                me->set_short_desc(0);
                me->command("halt");
                return 1;
        }

        message_vision(YEL + "$N" + (random(2) ? "疯狂地" : "冷静地") + (random(2) ? "击打" : "攻击") + (random(2) ? "阵图" : "魔像") +
                //"<耐久:"+ to_string(query("xiang_life")) + "/" + to_string(query("xiang_maxlife")+query("apply/xiang_maxlife")) + ">\n" + NOR,  me);
                sprintf( YEL "%-3s%4d\n" NOR, (random(2) ? ".." : "..."), query("xiang_life")), me);

       //if (isnpc)     {}

        addn("xiang_life", -1);
        if (query("xiang_life") < 1) {
                        CHANNEL_D->channel_broadcast("rumor", NOR + MAG + "据说" + dtname + "洞天被玩家们攻破。\n" NOR);
                        message_vision(append_color(NOR YEL "魔像阵图已经被$N" NOR YEL "攻破，天旋地转之中洞天一阵扭曲。\n" NOR, YEL), me);
                                t = me->query_team();
                                n = sizeof(t);
                                if (n)
                                {
                                        foreach(tob in t)
                                        {
                                                if (objectp(tob) && playerp(tob) && environment(tob) == environment(me))
                                                {
                                                        tell_object(tob, "\n" + HIY + dtname + HIY + "护山大阵的阵图已破，你的队伍已经成为洞天的新主人。\n" + NOR);
                                                        owns += ({query("id", tob)});
                                                        if (tob->in_team() && tob->is_team_leader()) {
                                                                coupid = query("couple/couple_id", tob);//队长的老婆
                                                                if (coupid) {
                                                                        tell_object(tob, "\n" + HIY + dtname + HIY + "护山大阵的阵图已破，你的伴侣(" + coupid + ")也成为了洞天的新主人。\n" + NOR);
                                                                        owns += ({coupid});
                                                                }
                                                        }
                                                }
                                        }
                                }
                                else
                                {
                                                        tell_object(me, "\n" + HIY + dtname + HIY + "护山大阵的阵图已破，你已经成为洞天的新主人。\n" + NOR);
                                                        owns += ({query("id", me)});
                                                        coupid = query("couple/couple_id", me);
                                                        if (coupid) owns += ({coupid});
                                }

                        set("enhance/xiang_maxlife", 50*query("zhen_type"));
                        set("enhance/num_yanxi", 300*query("zhen_type"));
                        ti1 = query("enhance/xiang_maxlife");
                        ti2 = query("enhance/num_yanxi");
                        __DIR__"data.c"->do_clear();
                set("hold_time", time());
                set("owners", owns);
                        __DIR__"data.c"->do_save("hold_time", query("hold_time"));
                        __DIR__"data.c"->do_save("owners", query("owners"));
                        __DIR__"data.c"->do_save("enhance/xiang_maxlife", ti1);
                        __DIR__"data.c"->do_save("enhance/num_yanxi", ti2);
                        reload_object(this_object());
                        set("protect_time", time() + 7200);
                delete("attacker_player");
                        me->set_short_desc(0);
                me->command("halt");
                do_expel_allusers();
        } /*else if (query("xiang_life") % 50 == 0 || !random(query("xiang_life")+3)) {
                        obs = filter_array(all_inventory(this_object()),
                           (: playerp($1) &&
                           //query("dongtian/my/dtname", $1) != dtname
                           !owner_level($1)
                           :));

                while (npci--) {
                                ob = new(__DIR__"npc/guarder");
                                plv = query("guarder_level") / 10;
                                if (plv > 30) plv = 30;
                                if (plv < 10) plv = 10;
                                set("guarder_level", query("guarder_level") + plv, ob);
                                set("nflee", time() + 45 + random(15) + query("guarder_lifetime"), ob);
                                ob->do_copyskill();
                                ob->move(this_object());
                                set("name", dtname + query("name", ob), ob);
                                //ob->set_leader(me);
                                set("enemy_player", me, ob);
                                ob->stop_busy();
                        ob->command("get all");
                        ob->stop_busy();
                        ob->command("exert powerup");
                        ob->stop_busy();
                        ob->command("exert shield");
                        ob->stop_busy();
                        ob->command("exert zu");
                        ob->stop_busy();
                        for( i = 0; i < sizeof(obs); i++ ) {
                                        ob->kill_ob(obs[i]);
                                }
                                ob->kill_ob(me);
                        }
        }*/
        return 1;
}

int do_break()
{//攻击阵图时，全广场的非主人玩家受反击
        object me = this_player();
        object previous = query("attacker_player");

        if (me->is_busy())
                return notify_fail(NOR "你还是忙完再说吧。\n" NOR);
        if (me->is_fighting())
                return notify_fail(NOR "你还是打完架再说吧。\n" NOR);

        me->start_busy(2);

        if (query_temp("apply/shade_vision", me))
                        return notify_fail( NOR "你在隐身里不可耍赖。\n" NOR);

        if (owner_level(me))
                return notify_fail( NOR "你就是这洞天的一员呢。\n" NOR);

        if (base_name(me)=="/clone/user/baby")
                return notify_fail(NOR "小孩儿别来趟浑水。\n" NOR);

        if (wiz_level(me) == 1)
                return notify_fail(NOR "你是新手导师，别来趟浑水。\n" NOR);

        if (query("xiang_life") < 1)
                return notify_fail(NOR "此处大阵已破，无需攻打。\n" NOR);

        if (query("protect_time") > time())
                return notify_fail(NOR "此处洞天处于两小时保护中。\n" NOR);

        if (query("hold_time") == query_temp("dongtian/invite/hold_time", me))
                return notify_fail(NOR "你忘记你怎么进来的了？脑后生有反骨吧。\n" NOR);

        if (query("hold_time") == query_temp("dongtian/houshan/hold_time", me))
                return notify_fail(NOR "你忘记你怎么进来的了？低调点吧。\n" NOR);

        if ( previous && objectp(previous) && environment(previous) == this_object())
                return notify_fail(NOR + query("name", previous) + "正在攻击阵图。\n" + NOR);

        set("attacker_player", me);

    me->start_busy((: call_other, __FILE__, "attacking" :),
                       (: call_other, __FILE__, "halt_attacking" :));

        me->set_short_desc("正在攻击阵图。");
        //write(NOR "你开始攻击护山大阵的阵图，<halt>可以中止。\n" NOR);
        write(NOR "你开始攻击护山大阵阵图。\n" NOR);
        //CHANNEL_D->channel_broadcast("debug", NOR + HIW + "洞天福地：" + query("id", me) + "开始攻击" + dtname + " " + base_name(this_object()) + " \n" + NOR);
        if (query_temp("attk_time") < time()) {
                set_temp("attk_time", time() + 270);
                CHANNEL_D->channel_broadcast("dt", NOR + HIW + "据说" + HIC + dtname + "洞天" + query("zhen_lvname") + NOR + HIW + "正遭受猛烈攻击。\n" + NOR);
        }
        return 1;
}

int do_break2(object me)//掠夺专用
{
        object previous = query("attacker_player");

        if (query("hold_time") < 2) return 1;//已经是npc的洞天

        if (me->is_busy())
                return notify_fail(NOR "你还是忙完再说吧。\n" NOR);
        if (me->is_fighting())
                return notify_fail(NOR "你还是打完架再说吧。\n" NOR);

        if (query("xiang_life") < 1)
                return notify_fail(NOR "此处大阵已破，无需攻打。\n" NOR);

        if (query("protect_time") > time())
                return notify_fail(NOR "此处洞天处于两小时保护中。\n" NOR);

        if ( previous && objectp(previous) && environment(previous) == this_object() && previous != me)
                return notify_fail(NOR + query("name", previous) + "正在攻击阵图。\n" + NOR);

        set("attacker_player", me);
        remove_call_out("halt_attacking2");
        call_out("halt_attacking2", 3 + random(7));
        attacking(me);
        return 1;
}


int do_imbue(string arg)
{
        object me = this_player();
        object *inv;
        int i, quality;
        object ob;
        int damage = 100, fatalblow = 2, attack = 48;
        mapping weap = ([]);
        string act = "击";

        if( me->is_busy()) {
                return notify_fail( NOR "你现在正忙着呢。\n" NOR);
        }

        if (!arg || arg=="") {
                return notify_fail( NOR "指令格式:<imb 武器id> <imb none>\n" NOR);
        }

        me->start_busy(4);

        if (owner_level(me) <2 && wiz_level(me) < 5) //非洞天的主人之一
                return notify_fail( NOR "你不是这个洞天的主人！\n" NOR);

        if (arg == "none") {
                if (!__DIR__"data.c"->do_load("xiang_weapons"))
                        return notify_fail( NOR "阵图上已经没有任何武器了。\n" NOR);

                __DIR__"data.c"->do_save("xiang_weapons", 0);
                delete("xiang_weapons");
                message_vision(append_color(NOR CYN "$N" NOR CYN "低头祷告，魔神雕像六臂一振，手上的兵器全部化为齑粉。\n" NOR, CYN), me);
                return 1;
        }

        ob = present(arg, me);

        if( !ob )
        {
                inv = all_inventory(me);
                for( i = 0; i < sizeof(inv); i++ )
                {
                        if( filter_color(inv[i]->name(1)) == arg )
                        {
                                ob = inv[i];
                                break;
                        }
                }
        }

        if ( !objectp(ob) )
        {
                return notify_fail( NOR "你身上没有这件武器。\n" NOR);
        }

                        if (sscanf(base_name(ob), "/inherit/template/weapon/%*s") ||
                                sscanf(base_name(ob), "/inherit/template/armor/finger%*s") ||
                                sscanf(base_name(ob), "/inherit/template/armor/hands%*s")
                                ) {
                                damage += query("weapon_prop/damage", ob);
                                damage += query("weapon_prop/unarmed_damage", ob);
                                damage += query("armor_prop/damage", ob);
                                damage += query("armor_prop/unarmed_damage", ob);
                                damage *= 25 + 3 * (to_int(query("weapon_prop/da_power", ob)) + to_int(query("armor_prop/da_power", ob)) + to_int(query("enchase/apply_prop/da_power", ob)));
                                damage += query("enchase/apply_prop/damage", ob) * 2;
                                damage += query("enchase/apply_prop/unarmed_damage", ob) * 2;
                                damage += query("weapon_prop/max_qi", ob);
                                damage += query("armor_prop/max_qi", ob);
                                damage += query("enchase/apply_prop/max_qi", ob);
                                damage += query("weapon_prop/max_jing", ob);
                                damage += query("armor_prop/max_jing", ob);
                                damage += query("enchase/apply_prop/max_jing", ob);
                                damage += query("weapon_prop/max_jingli", ob);
                                damage += query("armor_prop/max_jingli", ob);
                                damage += query("enchase/apply_prop/max_jingli", ob);
                                damage += query("weapon_prop/max_neili", ob);
                                damage += query("armor_prop/max_neili", ob);
                                damage += query("enchase/apply_prop/max_neili", ob);
                                damage *= 10000 + 350 * sizeof(query("enchase/apply_prop", ob)) + 450 * sizeof(query("weapon_prop", ob)) + 350 * sizeof(query("armor_prop", ob));
                                damage /= 10000 + ( (random(2))? (random(100)) : (-random(100)) );

                                fatalblow += to_int(query("weapon_prop/fatal_blow", ob)) * 2;
                                fatalblow += to_int(query("weapon_prop/double_damage", ob));
                                fatalblow += to_int(query("weapon_prop/add_damage", ob));
                                fatalblow += to_int(query("weapon_prop/str", ob));
                                attack += to_int(query("weapon_prop/ap_power", ob)) * 3;
                                attack += to_int(query("weapon_prop/kar", ob)) * 2;
                                attack += to_int(query("weapon_prop/int", ob));
                                attack += to_int(query("weapon_prop/dex", ob));

                                fatalblow += to_int(query("armor_prop/fatal_blow", ob)) * 2;
                                fatalblow += to_int(query("armor_prop/double_damage", ob));
                                fatalblow += to_int(query("armor_prop/add_damage", ob));
                                fatalblow += to_int(query("armor_prop/str", ob));
                                attack += to_int(query("armor_prop/ap_power", ob)) * 3;
                                attack += to_int(query("armor_prop/kar", ob)) * 2;
                                attack += to_int(query("armor_prop/int", ob));
                                attack += to_int(query("armor_prop/dex", ob));

                                fatalblow += to_int(query("enchase/apply_prop/fatal_blow", ob)) * 2;
                                fatalblow += to_int(query("enchase/apply_prop/double_damage", ob));
                                fatalblow += to_int(query("enchase/apply_prop/add_damage", ob));
                                fatalblow += to_int(query("enchase/apply_prop/str", ob));
                                attack += to_int(query("enchase/apply_prop/ap_power", ob)) * 3;
                                attack += to_int(query("enchase/apply_prop/kar", ob)) * 2;
                                attack += to_int(query("enchase/apply_prop/int", ob));
                                attack += to_int(query("enchase/apply_prop/dex", ob));

                                fatalblow += random(sizeof(query("weapon_prop", ob)) + sizeof(query("armor_prop", ob)));
                                attack += random(sizeof(query("enchase/apply_prop", ob)));

                                quality = query("quality_level", ob);
                                if (!quality || quality < 1) quality = 1;
                                attack += quality - 2;
                                fatalblow += quality - 2;
                                damage *= quality * quality;

                                switch (query("skill_type", ob)) {
                                        case "blade":
                                        case "axe":
                                                act = "劈";
                                                break;
                                        case "xsword":
                                        case "sword":
                                        case "spear":
                                        case "dagger":
                                        case "pin":
                                                act = "刺";
                                                break;
                                        case "whip":
                                        case "staff":
                                                act = "抽";
                                                break;
                                        case "throwing":
                                                act = "射";
                                                break;
                                        case "hammer":
                                        case "club":
                                        case "mace":
                                                act = "砸";
                                                break;
                                }

                                if (sscanf(base_name(ob), "/inherit/template/armor/finger%*s"))
                                        act = "戳";
                                if (sscanf(base_name(ob), "/inherit/template/armor/hands%*s"))
                                        act = "拍";

                        weap = __DIR__"data.c"->do_load("xiang_weapons");
                        if (undefinedp(weap) || !weap || !sizeof(weap) || !mapp(weap)) {
                                __DIR__"data.c"->do_save("xiang_weapons", ([
                                                "name"  :       query("name", ob),
                                                "colorname"     :       query("colorname", ob),
                                                "unit"  :       query("unit", ob),
                                                "act"   :       act,
                                                "damage"        :       damage,
                                                "fatalblow"     :       fatalblow,
                                                "attack"        :       attack,
                                                "number"        :       0,
                                        ]));
                        }
                        else {
                                if (weap["number"] > query("zhen_type"))
                                        return notify_fail( NOR "阵图等级不足！\n" NOR);

                                if (random(fatalblow) > weap["fatalblow"] / 2)
                                        fatalblow = 1;
                                else
                                        fatalblow = 0;

                                if (random(attack) > weap["attack"] * 2 / 3)
                                        attack = 1;
                                else
                                        attack = 0;

                                damage /= 8;

                                __DIR__"data.c"->do_save("xiang_weapons", ([
                                                "name"  :       weap["name"],
                                                "colorname"     :       weap["colorname"],
                                                "unit"  :       weap["unit"],
                                                "act"   :       weap["act"],
                                                "damage"        :       weap["damage"] + damage,
                                                "fatalblow"     :       weap["fatalblow"] + fatalblow,
                                                "attack"        :       weap["attack"] + attack + ((query("quality_level", ob) > 3) ? query("quality_level", ob) - 3 : 0),
                                                "number"        :       weap["number"] + 1,
                                        ]));
                        }

                                message_vision(append_color(NOR CYN "$N举起一" + query("unit", ob) + query("colorname", ob) + NOR + CYN + "虔诚地献到魔神雕像的手上。\n" NOR, CYN), me);
                                destruct(ob);
                                //write(NOR "你把武器嵌入了阵图，更新还要稍后。\n");
                                return 1;
                        }

        return notify_fail( NOR "你想嵌入的这个是啥武器！？\n" NOR);
}

string load_weapon()
{
        mapping weap = ([]);
        weap = __DIR__"data.c"->do_load("xiang_weapons");
        set("xiang_weapons", weap);
        if (!weap || !sizeof(weap))
                return NOR "无" NOR;
        else {
                return sprintf("%s" NOR "-> 伤害+%d,命中+%d,暴击+%d (+%d)", weap["colorname"], weap["damage"]+query_dt_qy(), weap["attack"], weap["fatalblow"], weap["number"]);
        }
        return NOR "无" NOR;
}

int do_kneel(string arg)
{
        object me = this_player();

        if (!arg || arg!="xiang")
                return notify_fail(NOR + "你想膜拜什么？\n" + NOR);

        if (me->is_busy()) return notify_fail(NOR + "你现在正忙。\n" + NOR);
        me->start_busy(3);

        message_vision(append_color(NOR + YEL + "$N" + NOR + YEL + "对着魔像鞠躬拜了三拜。\n" + NOR, YEL), me);
        add_ownlist(me);
        return 1;
}

string look_xiang(object me)
{
        if (me->is_busy()) return NOR"你现在正忙。\n"NOR;
        me->start_busy(3);

        add_action("do_kneel", "kneel");
        return
HIK + "『" + query("zhen_lvname") + HIK + "阵图』" + HIY + repeat_string("★", query("zhen_type")) + "\n" + NOR
YEL
"这是一尊庄严的魔神雕像，脚踩腾蛇拉着的战辇，披挂麒麟甲。\n"
"这丈六金身三头六臂，脸呈欢喜冷漠狰狞像，每支手臂各持武器，\n"
"其中显眼的是" NOR YEL "［" + load_weapon() + NOR + YEL  "］\n"
HIK
"耐久:"+ to_string(query("xiang_life")) + "/" + to_string(query("xiang_maxlife")+query("apply/xiang_maxlife")) + " (break-破坏, upg-升级, imb-嵌入)\n"
"\n" +
NOR +
"你看完后有种想膜拜(kneel xiang)的冲动..\n" + NOR;
}

int chk_zhenlv()
{
        int lv, lifetime = 0, level = 0, pro = 0;

        level = query("guarder_level");
        lifetime = query("guarder_lifetime");
        pro = query("guarder_pro");

                if (lifetime >= 100 && level >= 300 && pro >= 50)
                        set("zhen_type", 5);
                else if (lifetime >= 80 && level >= 200 && pro >= 40)
                        set("zhen_type", 4);
                else if (lifetime >= 60 && level >= 150 && pro >= 30)
                        set("zhen_type", 3);
                else if (lifetime >= 40 && level >= 100 && pro >= 20)
                        set("zhen_type", 2);
                else if (lifetime >= 20 && level >= 50 && pro >= 10)
                        set("zhen_type", 1);
                else
                        set("zhen_type", 0);

        lv = query("zhen_type");
        set("zhen_lvname", SHORTZHEN[lv]);
        return lv;
}

int rndnum(int i)
{
        return i*9/10 + random(i/5);
}

int set_sys_owner()
{
        mapping *xweap = ({
                        ([
                                "name"          : "紫青双剑",
                                "colorname"     : NOR BRED HIM "紫" NOR BRED CYN "青" YEL "双剑" NOR,
                                "unit"          : "对",
                                "act"           : "绞",
                                "damage"        :       rndnum(10000000),
                                "fatalblow"     :       12 + random(3),
                                "attack"        :       79 + random(5),
                                "number"        :       9,
                        ]),
                        ([
                                "name"          : "诛仙剑",
                                "colorname"     : NOR BRED HIC "诛仙剑" NOR,
                                "unit"          : "柄",
                                "act"           : "斩",
                                "damage"        :       rndnum(11000000),
                                "fatalblow"     :       10 + random(3),
                                "attack"        :       76 + random(5),
                                "number"        :       9,
                        ]),
                        ([
                                "name"          : "盘古幡",
                                "colorname"     : NOR BRED HIB "盘古幡" NOR,
                                "unit"          : "杆",
                                "act"           : "扫",
                                "damage"        :       rndnum(12000000),
                                "fatalblow"     :       8 + random(3),
                                "attack"        :       73 + random(5),
                                "number"        :       9,
                        ]),
                        ([
                                "name"          : "混沌钟",
                                "colorname"     : NOR BRED YEL "混沌钟" NOR,
                                "unit"          : "尊",
                                "act"           : "砸",
                                "damage"        :       rndnum(13000000),
                                "fatalblow"     :       6 + random(3),
                                "attack"        :       70 + random(5),
                                "number"        :       9,
                        ]),
                });
        int rndzlv = random(5) + 1;

        __DIR__"data.c"->do_clear();

        set("guarder_lifetime", 20*rndzlv+ random(80));
        set("guarder_level", 50*rndzlv+ random(200));
        set("guarder_pro", 10*rndzlv+ random(40));
        set("apply/xiang_maxlife", random(450) + 450);
        set("apply/xiang_repair", random(5) + 5);
        set("apply/num_yanxi", random(2500) + 500);
        set("apply/num_jisi", 5000);
//      set("enhance/xiang_maxlife", 50*rndzlv);
//      set("enhance/num_yanxi", 300*rndzlv);
        __DIR__"data.c"->do_save("guarder_level", query("guarder_level"));
        __DIR__"data.c"->do_save("guarder_lifetime", query("guarder_lifetime"));
        __DIR__"data.c"->do_save("guarder_pro", query("guarder_pro"));
        __DIR__"data.c"->do_save("apply/xiang_maxlife", query("apply/xiang_maxlife"));
        __DIR__"data.c"->do_save("apply/xiang_repair", query("apply/xiang_repair"));
        __DIR__"data.c"->do_save("apply/num_yanxi", query("apply/num_yanxi"));
        __DIR__"data.c"->do_save("apply/num_jisi", query("apply/num_jisi"));
        //__DIR__"data.c"->do_save("apply", query("apply"));
//      __DIR__"data.c"->do_save("enhance/xiang_maxlife", query("enhance/xiang_maxlife"));
//      __DIR__"data.c"->do_save("enhance/num_yanxi", query("enhance/num_yanxi"));

        __DIR__"data.c"->do_save("xiang_weapons", xweap[random(sizeof(xweap))]);

        set("hold_time", 1);
        __DIR__"data.c"->do_save("hold_time", query("hold_time"));
        tell_room(this_object(), NOR HIY "\n重设了洞天为NPC所有！\n\n" NOR);
        return 1;
}

int reload_me()
{
        set("hold_time", __DIR__"data.c"->do_load("hold_time"));
        if (undefinedp(query("hold_time")) || !query("hold_time")) {
                set_sys_owner();
                reload_object(this_object());
                return 1;
        }
        dtname = load_name();
        set("short", HIC + dtname + "广场" + NOR);
        set("owners", __DIR__"data.c"->do_load("owners"));
        set("guarder_lifetime", __DIR__"data.c"->do_load("guarder_lifetime"));
        set("guarder_level", __DIR__"data.c"->do_load("guarder_level"));
        set("guarder_pro", __DIR__"data.c"->do_load("guarder_pro"));
        set("apply/xiang_maxlife", __DIR__"data.c"->do_load("apply/xiang_maxlife"));
        set("apply/xiang_repair", __DIR__"data.c"->do_load("apply/xiang_repair"));
        set("apply/num_yanxi", __DIR__"data.c"->do_load("apply/num_yanxi"));
        set("apply/num_jisi", __DIR__"data.c"->do_load("apply/num_jisi"));
        //set("apply", __DIR__"data.c"->do_load("apply"));
        set("enhance/xiang_maxlife", __DIR__"data.c"->do_load("enhance/xiang_maxlife"));
        set("enhance/num_yanxi", __DIR__"data.c"->do_load("enhance/num_yanxi"));

        chk_zhenlv();
        load_weapon();
        return 1;
}

int do_smash2(object me, object ob, object where)
{
        string msg = NOR;
        mapping weap = query("xiang_weapons");
        int jiali, arnd, bflag, flag, nl, i, mx, zlv = query("zhen_type");
        int damage = 0, fatalblow = 0, attack = 0;

        if (!me || !ob || !objectp(me) || !objectp(ob) || !objectp(where) || !objectp(environment(ob)) || environment(ob)!=where) {
                if (objectp(ob)) delete_temp("dongtian/smash_step", ob);
                return 0;
        }
        delete_temp("dongtian/smash_step", ob);
        if (undefinedp(weap) || !weap || !sizeof(weap) || !mapp(weap)) {
                return 0;
        }
        if (me->is_character()) {
                if (!objectp(environment(me)) || environment(me)!=where) {
                        return 0;
                }
                me->start_busy(2);
        }
        ob->start_busy(2);

        if (zlv<1)
                mx = 1;
        else if (zlv<2)
                mx = 2;
        else if (zlv<4)
                mx = 3;
        else if (zlv<5)
                mx = 6;
        else
                mx = 9;

        jiali = query("jiali", me);
        jiali -= 2000;
        if (jiali < 0) jiali = 0;
        jiali /= 60;
        //if (!playerp(me)) jiali /= 100;
        for (i = 0; i < mx; i++) {
                if (environment(ob)!=where) break;
                attack = weap["attack"];
                arnd = random(100);
                flag = attack > arnd;

                        damage = weap["damage"] * THUNDER_DAMAGE_PERCENT / 100;
                        damage += query_dt_qy();
                        if (!playerp(ob)) {
                                damage *= (100 + jiali) / 100;
                                if (playerp(me)) {
                                        damage *= 150;//pvn再放大150倍
                                }
                        }
                        fatalblow = weap["fatalblow"];
                        bflag = random(100)<fatalblow;
                        if (bflag) {
                                damage *= 5 / 2;
                        } else {
                                damage = damage * 3 / 4 + random(damage / 4);
                        }

                msg = NOR + CYN + (random(2) ? "天上":"云中") +
                        NOR + HIY + (random(2) ? "显现":"凝聚出") + "一" +
                        NOR + HIY + weap["unit"] +
                        NOR + BLINK + weap["colorname"] +
                        NOR + HIY + "，" + (random(2) ? "挟":"挈") + "着" + NOR + BLINK + (random(2) ? (YEL + "闪电"): (HIR + "雷火"))  +
                        NOR + HIY + (random(2) ? "摧枯拉朽地":"势不可当地") +  weap["act"] + (random(2) ? "往":"向") + "$N" + NOR + HIY + "。"+
                        NOR + HIK + "  ( " + (flag ? ((bflag ? NOR + BLINK + WHT + "暴击" : NOR + WHT + "伤害") + "：" + to_string(damage)) : ("失败：" + to_string(attack) + " > " + to_string(arnd))) + NOR + HIK + " )\n" + NOR ;
                message_vision(msg, ob);
                if (flag) {
                        addn("qi", -damage, ob);
                        if (query("qi", ob) < 1) set("qi", -1, ob);
                        addn("eff_qi", -damage/2, ob);
                        if (query("eff_qi", ob) < 1) set("eff_qi", -1, ob);
                        addn("jing", -damage/2, ob);
                        if (query("jing", ob) < 1) set("jing", -1, ob);
                        addn("eff_jing", -damage/4, ob);
                        if (query("eff_jing", ob) < 1) set("eff_jing", -1, ob);
                        addn("neili", -damage/16, ob);
                        if (query("neili", ob) < 1) set("neili", 0, ob);
                        if (attack / 2 > random(100)) {//极小地扣除精力内力，使药复用
                                nl = (zlv+1) * (zlv+1) + 3;
                                nl = random(nl) + nl / 2;
                                addn("max_jingli", - nl, ob);
                                if (query("max_jingli", ob) < 1) set("max_jingli", 0, ob);
                                addn("max_neili", - nl * 2, ob);
                                if (query("max_neili", ob) < 1) set("max_neili", 0, ob);
                                tell_object(ob, NOR + "( 你" + NOR + HIB + "在天雷劫火之下，损失了"+chinese_number(nl)+"点精力和"+chinese_number(nl*2)+"点内力修为。" + NOR + " )\n" + NOR);
                        }
                        COMBAT_D->report_status(ob);
                }
        }
        message_vision("\n", ob);

                        if (query("qi", ob) < 0 || query("jing", ob) < 0) {
                                set_temp("die_reason", NOR + HIR + "被" +
                                        ((me->is_character())? (NOR + HIR + query("name", me)):(NOR + HIR + query("zhen_lvname") + "魔像")) + NOR + HIR + "请来的" + dtname +
                                         weap["colorname"] + NOR + HIR + weap["act"] + "死了", ob);
                                ob->die();
                        }

        return 1;
}

int do_smash(object me, object ob, object where)
{
        object lian;
        string msg = NOR;
        if (!me || !ob || !objectp(me) || !objectp(ob) || !objectp(where) || !objectp(environment(ob)) || environment(ob)!=where) {
                if (objectp(ob)) delete_temp("dongtian/smash_step", ob);
                return 0;
        }
        if (me->is_character()) {
                if (!objectp(environment(me)) || environment(me)!=where) {
                        if (objectp(ob)) delete_temp("dongtian/smash_step", ob);
                        return 0;
                }
                me->start_busy(4);
        }
        ob->start_busy(4);

        lian = query_temp("armor/hairpin", ob);
        if (lian && objectp(lian) &&
                query("id", lian)=="qiyun lian" &&
                query("quality_level", lian)>query("zhen_type") &&
                random(3)) {
                message_vision(NOR + YEL + "$N" + NOR + YEL + "头戴的" + query("name", lian) + NOR + YEL + "微微一动，\n" +
                        "只见虚空破碎，" + HIC + query("dtname", lian) + NOR + YEL + "穿过来只巨掌，往空中一挥道：退～～\n" +
                        NOR + HIC + "漫天乌云立时消散，天上转赴清明，星空回复朗透...\n\n" + NOR, ob);
                if (objectp(ob)) delete_temp("dongtian/smash_step", ob);
                        return 0;
        }

        if (query_temp("dongtian/smash_step", ob) < 2 || (random(2) && query_temp("dongtian/smash_step", ob) < 3)) {
                addn_temp("dongtian/smash_step", 1, ob);
                message_vision(NOR + WHT + "天地灵气" + (random(2) ? "疯狂地聚集": (random(2) ? "狂躁":"浩荡") + "如潮") +
                        "，" + (random(2) ? (random(2) ? "天威":"如泰山") + "压得$N" + NOR + WHT + "动弹" + (random(2) ? "不得":"不了") + "。":"牵引着$N" + NOR + WHT + "转不了身。") + "\n\n" + NOR, ob);
                call_out("do_smash", random(2) + 1, me, ob, where);
        } else {
                if (me->is_character()) {
                        me->start_busy(4);
                        msg += NOR + CYN + "$N" + NOR + CYN + "五指往" + dtname + "方向虚招道：“煌煌" + NOR + query("zhen_lvname") + NOR + CYN + "，代吾殛之！”\n" + NOR;
                }
                msg += NOR + CYN + "若隐若显里" + NOR + YEL + dtname + NOR + query("zhen_lvname") + NOR + YEL + "魔像" + NOR + CYN + "声如洪钟，遥遥对着$n" + NOR + CYN + "咒曰：“九天玄刹～ 化为神雷～”\n\n" + NOR;
                //message_vision(msg, (me->is_character() ? me : ob));
                message_vision(msg, me, ob);
                call_out("do_smash2", 1, me, ob, where);
        }
        return 1;
}

int can_smash(object me, object ob, int chance)
{
        string msg = NOR;
        object where;
        mapping weap = query("xiang_weapons");
        if (!me || !ob)
                return 0;
        if (query_temp("flag_hslj", me) || query_temp("flag_hslj", ob))
                return 0;
        if (undefinedp(weap) || !weap || !sizeof(weap) || !mapp(weap))
                return 0;
        if (random(100) > chance)
                return 0;
        if (!query("apply/num_jisi"))//没祭祀能量
                return 0;
        where = environment(ob);
        if (!where || !objectp(where) || !where->is_room())
                return 0;
        if (query_temp("dongtian/smash_step", ob))
                return 0;
        if (me->is_character()) me->start_busy(4);
        ob->start_busy(4);
        set_temp("dongtian/smash_step", 1, ob);
        if (!query_temp("dongtian/smash_time", where) || query_temp("dongtian/smash_time", where) < time()) {
                set_temp("dongtian/smash_time", time() + 15, where);
                msg = NOR + HBWHT + HIC + "\n忽然间，\n" + HIY + "雷声滚滚，\n" + HIB + "乌云密布..\n" + NOR;
                tell_room(where, msg);
        }
                if (me->is_character()) {
                        me->start_busy(4);
                        msg = NOR + CYN + me->name() + NOR + CYN + "踏罡布斗，口里念念有词：“使吾之剑，以为雷引...”\n" + NOR;
                        tell_room(where, msg);
                }
        call_out("do_smash", 1, me, ob, where);
        return 1;
}

int create_reqitem()
{
        string strt, *strk = ({});
        int lv, i;
        int lifetime = 0, level = 0, pro = 0;

        if (!query("flag_init")) reload_object(this_object());

        level = query("guarder_level");
        lifetime = query("guarder_lifetime");
        pro = query("guarder_pro");

        if (!query("upg/require/1")) {
                if (level >= 200)
                        lv = 4;
                else if (level >= 150)
                        lv = 3;
                else if (level >= 100)
                        lv = 2;
                else if (level >= 50)
                        lv = 1;
                else
                        lv = 0;
                strk = keys(REQ_ITEMS[lv]);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/1/" + strt, REQ_ITEMS[lv][strt]);
                }
                set("upg/require_quality_level/1", lv + 2);
        }
        if (!query("upg/require/2")) {
                if (lifetime >= 80)
                        lv = 4;
                else if (lifetime >= 60)
                        lv = 3;
                else if (lifetime >= 40)
                        lv = 2;
                else if (lifetime >= 20)
                        lv = 1;
                else
                        lv = 0;
                strk = keys(REQ_ITEMS[lv]);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/2/" + strt, REQ_ITEMS[lv][strt]);
                }
                set("upg/require_quality_level/2", lv + 2);
        }
        if (!query("upg/require/3")) {
                if (pro >= 40)
                        lv = 4;
                else if (pro >= 30)
                        lv = 3;
                else if (pro >= 20)
                        lv = 2;
                else if (pro >= 10)
                        lv = 1;
                else
                        lv = 0;
                strk = keys(REQ_ITEMS[lv]);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/3/" + strt, REQ_ITEMS[lv][strt]);
                }
                set("upg/require_quality_level/3", lv + 2);
        }
        if (!query("upg/require/4")) {
                strk = keys(REQ_ITEMS[1]);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/4/" + strt, REQ_ITEMS[1][strt]);
                }
        }
        if (!query("upg/require/5")) {
                strk = keys(REQ_ITEMS[0]);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/5/" + strt, REQ_ITEMS[0][strt]);
                }
        }
        if (!query("upg/require/6")) {
                strk = keys(REQ_ITEMS2);
                for( i = 0; i < 3; i++ ) {
                        strt = strk[random(sizeof(strk))];
                        strk -= ({strt});
                        set("upg/require/6/" + strt, REQ_ITEMS2[strt]);
                }
        }

        return 1;
}

string sort_itemnames(int idx)
{
        int i, j;
        string msg = "", *strk = ({});
        if (!query("upg/require/" + to_string(idx)))
                return "无";//不能出现
        strk = keys(query("upg/require/" + to_string(idx)));
        j = sizeof(strk);
        for( i = 0; i < j; i++ ) {
                msg += strk[i];
                if (i < j - 1) msg +=",";
        }
        return msg;
}

int chk_reqitems(object me, int idx)
{
        int i, j, k, flag, count = 0;
        string file, obname, *strk = ({});
        object ob, *inv, *obs = ({});
        int max_amount;

        if (!query("upg/require/" + to_string(idx)))
                return 0;//不能出现
        strk = keys(query("upg/require/" + to_string(idx)));
        j = sizeof(strk);
        inv = all_inventory(me);
        if (wiz_level(me) < 5 && sizeof(inv) > 60) {
                tell_object(me, NOR "你身上的物品超过了60件。\n" NOR);//减负检查环节
                return 0;
        }

        for( i = 0; i < j; i++ ) {
                obname = strk[i];
                file = query("upg/require/" + to_string(idx))[obname];
                //write (obname + " - " + file + "\n");
                flag = 0;
                for( k = 0; k < sizeof(inv); k++ )
                {
                        if( query("item_owner", inv[k]) ) continue;    // 干将圣符upg过的物品无效
                        if( base_name(inv[k]) == "/d/dongtian/obj/liudibi" ) {
                                ob = inv[k];
                                message_vision(append_color(NOR CYN "$N举起" + query("name", ob) + NOR + CYN + "虔诚地献到魔神雕像的手上。\n" NOR, CYN), me);
                                destruct(ob);
                                delete("upg/require/" + to_string(idx));
                                create_reqitem();
                                return 1;
                        }

                        if( base_name(inv[k]) == file ) //加入判断品质神器传说史诗
                        {
                                if (sscanf(base_name(inv[k]), "/inherit/template/weapon/%*s") || sscanf(base_name(inv[k]), "/inherit/template/armor/%*s")) {
                                                if (query("quality_level", inv[k]) && query("quality_level", inv[k]) == query("upg/require_quality_level/" + to_string(idx))) {
                                                        flag = 1;
                                                        count += 1;
                                                        obs += ({inv[k]});
                                                        break;
                                                }
                                        }
                                else {
                                        flag = 1;
                                        count += 1;
                                        obs += ({inv[k]});
                                        break;
                                }
                        }
                }

        if ( !flag )
        {
                tell_object(me, NOR "你身上没有携带" + obname + "。\n" NOR);
        }
        }

        //write ("j:" + to_string(j) + " count:" + to_string(count) + "\n");
        if (j == count) {
                for( i = 0; i < sizeof(obs); i++ ) {
                        ob = obs[i];
                        obname = query("name", ob);
                        //write ("献祭" + obname + "。\n");
                        max_amount = ob->query_amount();
                        if (!max_amount || max_amount < 2) {
                                destruct(ob);
                        } else {
                                ob->add_amount(-1);
                        }
                        message_vision(append_color(NOR CYN "$N举起" + obname + NOR + CYN + "虔诚地献到魔神雕像的手上。\n" NOR, CYN), me);
                }
                delete("upg/require/" + to_string(idx));
                create_reqitem();
                return 1;
        }
        else if (j > count) {
                //tell_object(me, "你身上的需求物品不足。\n");
                return 0;
        }
        return 0;
}

int chk_reqtcash(object me, int amount)
{
        int i, k, flag;
        string file, obname;
        object ob, *inv;
        int max_amount;

        inv = all_inventory(me);
        if (wiz_level(me) < 5 && sizeof(inv) > 50) {
                tell_object(me, NOR "你身上的物品超过了50件。\n" NOR);//减负检查环节
                return 0;
        }

                obname = "千两金票";
                file = "/clone/money/thousand-gold";
                //write (obname + " - " + file + "\n");
                flag = 0;
                for( k = 0; k < sizeof(inv); k++ )
                {
                        if( base_name(inv[k]) == file )
                        {
                                        flag = 1;
                                        ob = inv[k];
                                        break;
                        }
                }

        if ( !flag )
        {
                tell_object(me, NOR "你身上没有携带" + obname + "。\n" NOR);
                return 0;
        }

                        max_amount = ob->query_amount();
                        if (!max_amount || max_amount < amount) {
                        tell_object(me, NOR "你身上携带的" + obname + "数量不足。\n" NOR);
                return 0;
            } else if (max_amount == amount) {
                                destruct(ob);
                        } else {
                                ob->add_amount(-amount);
                        }
                        message_vision(append_color(NOR CYN "$N举起" + chinese_number(amount) + query("unit", ob) + obname + NOR + CYN + "虔诚地献到魔神雕像的手上。\n" NOR, CYN), me);

                return 1;
}

int do_upg(string arg)
{
        object me = this_player();
        string msg, oldzhenname;
        int old, val;

        if( me->is_busy()) {
                return notify_fail( NOR "你现在正忙着呢。\n" NOR);
        }

        if (wiz_level(me) < 5) me->start_busy(4);

        oldzhenname = query("zhen_lvname");
        old = chk_zhenlv();
        create_reqitem();

        //msg = HIK + "『" + query("zhen_lvname") + HIK + "阵图』" + HIY + repeat_string("★", query("zhen_type")) + NOR + "(前三项为零的洞天归于无主)\n" + NOR;
        msg = HIK + "『" + query("zhen_lvname") + HIK + "阵图』" + HIY + repeat_string("★", query("zhen_type")) + NOR + "\n" + NOR;
        msg += sprintf( YEL "╔----------------------------╦------------------------------------------╗\n" NOR );
        msg += sprintf( YEL "┃" HIC "⒈傀儡等级+8：" NOR CYN "%9d/600 "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_level"), sort_itemnames(1));
        msg += sprintf( YEL "┃" HIC "⒉傀儡生存时间+5：" NOR CYN "%5d/200 "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_lifetime"), sort_itemnames(2));
        msg += sprintf( YEL "┃" HIC "⒊傀儡出战机率+3：" NOR CYN "%5d/99  "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_pro"), sort_itemnames(3));
        msg += sprintf( YEL "┃" HIC "⒋阵图耐久+5：" NOR CYN "%9d/"+to_string(450+query("enhance/xiang_maxlife"))+" "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/xiang_maxlife"), sort_itemnames(4));
        msg += sprintf( YEL "┃" HIC "⒌阵图修复效率+1：" NOR CYN "%5d/9   "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/xiang_repair"), sort_itemnames(5));
        msg += sprintf( YEL "┃" HIC "⒍洞天研习次数+6：" NOR CYN "%5d/"+to_string(YANXI_NUM+query("enhance/num_yanxi"))+""YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/num_yanxi"), sort_itemnames(6));
        msg += sprintf( YEL "┃" HIC "⒎祭祀魔像：" NOR CYN "%11d/5000"YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/num_jisi"), "５００张千两金票");
        msg += sprintf( YEL "╚----------------------------╩------------------------------------------╝\n" NOR );
        msg += NOR "指令格式:<upg 序号>\n" NOR;

        if (!arg || arg=="" || sscanf(arg, "%d", val)!=1) {
                tell_object(me, msg);
                return 1;
        }

        if (!owner_level(me) && wiz_level(me) < 5) //非洞天的主人之一
                return notify_fail( NOR "你不是这个洞天的主人！\n" NOR);

        if (val < 1 || val > 7)
                return notify_fail( NOR "序号超出范围！\n" NOR);

        switch (val) {
                case 1:
                        if (query("guarder_level") >= 600) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 1) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("guarder_level", query("guarder_level") + 8);
                        __DIR__"data.c"->do_save("guarder_level", query("guarder_level"));
                        break;
                case 2:
                        if (query("guarder_lifetime") >= 200) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 2) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("guarder_lifetime", query("guarder_lifetime") + 5);
                        __DIR__"data.c"->do_save("guarder_lifetime", query("guarder_lifetime"));
                        break;
                case 3:
                        if (query("guarder_pro") >= 99) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 3) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("guarder_pro", query("guarder_pro") + 3);
                        __DIR__"data.c"->do_save("guarder_pro", query("guarder_pro"));
                        break;
                case 4:
                        if (query("apply/xiang_maxlife") >= 450 + query("enhance/xiang_maxlife")) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 4) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("apply/xiang_maxlife", query("apply/xiang_maxlife") + 5);
                        __DIR__"data.c"->do_save("apply/xiang_maxlife", query("apply/xiang_maxlife"));
                        break;
                case 5:
                        if (query("apply/xiang_repair") >= 9) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 5) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("apply/xiang_repair", query("apply/xiang_repair") + 1);
                        __DIR__"data.c"->do_save("apply/xiang_repair", query("apply/xiang_repair"));
                        break;
                case 6:
                        if (query("apply/num_yanxi") >= YANXI_NUM + query("enhance/num_yanxi")) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqitems(me, 6) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("apply/num_yanxi", query("apply/num_yanxi") + 6);
                        __DIR__"data.c"->do_save("apply/num_yanxi", query("apply/num_yanxi"));
                        break;
                case 7:
                        if (query("apply/num_jisi") >= 4000) return notify_fail( NOR "这项能力暂时没有必要去升级。\n" NOR);
                        if (query("apply/num_jisi") >= 5000) return notify_fail( NOR "阵图的这项能力已经升到顶级了！\n" NOR);
                        if (!chk_reqtcash(me, 500) && wiz_level(me) < 7) return notify_fail( NOR "阵图的升级失败！\n" NOR);
                        set("apply/num_jisi", 5000);
                        __DIR__"data.c"->do_save("apply/num_jisi", query("apply/num_jisi"));
                        break;
        }
        msg = NOR CYN "...\n\n" NOR;
        //msg = HIK + "『" + query("zhen_lvname") + HIK + "阵图』" + HIY + repeat_string("★", query("zhen_type")) + NOR + "(前三项为零的洞天归于无主)\n" + NOR;
        msg = HIK + "『" + query("zhen_lvname") + HIK + "阵图』" + HIY + repeat_string("★", query("zhen_type")) + NOR + "\n" + NOR;
        msg += sprintf( YEL "╔----------------------------╦------------------------------------------╗\n" NOR );
        msg += sprintf( YEL "┃" HIC "⒈傀儡等级+8：" NOR CYN "%9d/600 "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_level"), sort_itemnames(1));
        msg += sprintf( YEL "┃" HIC "⒉傀儡生存时间+5：" NOR CYN "%5d/200 "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_lifetime"), sort_itemnames(2));
        msg += sprintf( YEL "┃" HIC "⒊傀儡出战机率+3：" NOR CYN "%5d/99  "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("guarder_pro"), sort_itemnames(3));
        msg += sprintf( YEL "┃" HIC "⒋阵图耐久+5：" NOR CYN "%9d/"+to_string(450+query("enhance/xiang_maxlife"))+" "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/xiang_maxlife"), sort_itemnames(4));
        msg += sprintf( YEL "┃" HIC "⒌阵图修复效率+1：" NOR CYN "%5d/9   "YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/xiang_repair"), sort_itemnames(5));
        msg += sprintf( YEL "┃" HIC "⒍洞天研习次数+6：" NOR CYN "%5d/"+to_string(YANXI_NUM+query("enhance/num_yanxi"))+""YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/num_yanxi"), sort_itemnames(6));
        msg += sprintf( YEL "┃" HIC "⒎祭祀魔像：" NOR CYN "%11d/5000"YEL "┃" WHT "需求：" NOR HIK "%-36s" NOR YEL "┃\n" NOR, query("apply/num_jisi"), "５００张千两金票");
        msg += sprintf( YEL "╚----------------------------╩------------------------------------------╝\n" NOR );
        msg += HIG "第" + chinese_number(arg) + "项能力成功升级！\n" NOR;
        if (chk_zhenlv() > old) {
                msg += HIG + "恭喜" + dtname + HIG + "你将阵图升级为" + query("zhen_lvname") + "！！\n" NOR;
                CHANNEL_D->channel_broadcast("dt",  NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "的护山大阵，从" + oldzhenname + NOR + WHT + "演变为" + query("zhen_lvname") + NOR + WHT + "了。\n" + NOR);
                __DIR__"enter.c"->reload_me();
        }

        tell_object(me, msg);
        return 1;
}

void create()
{
                reload_me();
        set("long",
"这里是仙府前的广场，地面全部用汉白玉铺砌，亮光闪闪，一眼望去，\n"
"使人生出渺小之心。远方白云朵朵，恍若轻纱，竟然都在脚下漂浮。一尊气\n"
"象恢宏的巨石雕像("CYN"xiang"NOR")，牢牢屹立在广场中央。绕过雕像之后是一扇大石\n"
"门，其上包裹着密密的铜钉，一副坚不可摧的样子。从侧门望去有无数的傀\n"
"儡甲士，正列队拱卫着这重要门户。\n"
        );
                set("exits",([ /* sizeof() == 1 */
                        "out" : __DIR__"enter",
                        "north" : __DIR__"qianting",
                ]));

        set("item_desc", ([
                "雕像": (: look_xiang :),
                "像": (: look_xiang :),
                "xiang": (: look_xiang :),
        ]) );

                set("no_sleep_room",1);
                //set("no_magic", 1);//准许招武器
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_drift", 1);
                set("no_protect", 1);

                set("xiang_life", XIANG_MAXLIFE);
                set("xiang_maxlife", XIANG_MAXLIFE);
                //set("max_carry_user", 30);

                set("flag_init", 1);
        set_heart_beat(41);//很合适的素数
        set("pathstring", replace_string(base_name( this_object() ), "guangchang", ""));
        setup();
}

int discmds()
{
        tell_object(this_player(), "这里不允许你这样做。\n");
        return 1;
}

int do_clear()
{
        __DIR__"data.c"->do_clear();
        reload_object(this_object());
        return 1;
}

int do_sav(string arg)
{
        string key;
        int val;

        if (!arg || arg=="")
                return notify_fail(NOR"没有指定arg:key val！\n"NOR);

        if (sscanf(arg, "%s %d", key, val)!=2)
                return notify_fail(NOR"没有指定arg:key val！\n"NOR);

        return __DIR__"data.c"->do_save(key, val);
}

int do_invit(string arg)
{
        if (!arg || arg=="")
                return notify_fail(NOR"没有指定玩家id！\n"NOR);

        //set("dongtian/my/dtname", dtname, find_player(arg));
        return 1;
}

int do_settu(string arg)
{
        int i1, i2, i3;
        if (!arg || arg=="")
                return notify_fail(NOR"guarder_lifetime 100,guarder_level 300,guarder_pro 50！\n"NOR);

        if (sscanf(arg, "%d %d %d", i1, i2, i3)!=3)
                return notify_fail(NOR"guarder_lifetime 100,guarder_level 300,guarder_pro 50！\n"NOR);

        __DIR__"data.c"->do_save("guarder_lifetime", i1);
        __DIR__"data.c"->do_save("guarder_level", i2);
        __DIR__"data.c"->do_save("guarder_pro", i3);
        return 1;
}

void add_ownlist(object me)
{
        object *owns;

        if (!me->is_character()) return;

        if ((playerp(me) && interactive(me) && owner_level(me))
                || query("id", me) == "kuilei jiang") {
                owns = query("ownlist");
                if (undefinedp(owns) || !owns || !sizeof(owns))
                        set("ownlist",  ({me}));
                else if (member_array(me, owns) < 0)
                        set("ownlist",  owns + ({me}));

                tell_object(me, NOR HIG "你心里一动，似乎和魔像建立了某种心神联系。\n" NOR);
                if (query("apply/num_jisi")>=1000) tell_object(me, NOR CYN "你感到魔像微不可察地对你点了点头。\n" NOR);
                else tell_object(me, NOR CYN "你耳边传来一阵若有若无的声音道：饿...\n" NOR);
        } else {
                tell_object(me, NOR CYN "你耳边传来一阵若有若无的声音道：“滚……”\n" NOR);
        }
}

void init()
{
        object me = this_player();

        if ((playerp(me)) &&
                (!query("load_dt_time") || query("load_dt_time")+60 < time())) {//没有读取过，或者读取时间超过了一分钟
                        set("load_dt_time", time());
                        reload_me();
        }

        if ( wiz_level(me) > 5 ) {
                add_action("do_clear", "clear");
                add_action("save_name", "name");
                add_action("do_sav", "sav");
                add_action("do_settu", "settu");
                add_action("do_expel_allusers", "expel");
                //add_action("do_invit", "invit");
        }

        if ((playerp(me) && wiz_level(me) < 6) || (base_name(me)=="/clone/user/baby")) add_action("discmds", ({
                                                                "steal", "cast", "conjure", "array", "fight",
                                                                "quit", "home", "exit", "recall", "ansuan", "touxi",
                                                                "surrender", "chatroom", "rideto", "stab",
                                                                "guard", "ride", "hit", "array",  "battle", "accept",//"team",
                }));  //只可以下kill，但不准跑掉，死战。可以在此组队


                if (playerp(me) && interactive(me)) {
                        add_action("do_break", "break");
                        add_action("do_imbue", "imb");
                        add_action("do_upg", "upg");
                        get_object(__DIR__"zhenbaoge")->init_encounter(me);
                        get_object(__DIR__"cangjingge")->init_encounter(me);
                }

        if (owner_level(me)) {
                set_temp("dongtian/invite/hold_time", query("hold_time"), me);
        }


}

int valid_leave(object me, string dir)
{
        if (me->is_busy())
                return notify_fail(NOR "你还是忙完再说吧。\n" NOR);

        if (me->is_fighting())
                return notify_fail(NOR"你还是先解决目前的敌人吧！\n"NOR);

        if (!playerp(me) && (strsrch(base_name(me), "dongtian") == -1))
                return notify_fail(NOR"你不是玩家！\n"NOR);

        if (query("attacker_player") == me)
                return notify_fail(NOR"你必须先停止对阵图的攻击！\n"NOR);

        if ((strsrch(base_name(me), "dongtian") == -1) && dir == "north" && query("hold_time") < 2 && wiz_level(me) < 6) {//洞天非玩家所属
                return notify_fail(NOR"这洞天目前没有主人，你不先尝试(break)来占领？\n"NOR);
        }

        if (dir == "out" && owner_level(me)) {
                return notify_fail(NOR"你有洞天的通行权，从后山的传送阵出去吧。\n"NOR);
        }

        if (dir == "out") {
                delete_temp("dongtian/houshan", me);
        }

        return ::valid_leave(me, dir);
}

/*int place_boss()
{
        string fil;
        string *flist = ({"huashan-pantu", "chaoting-taofan", "yan-ji", "tian-boguang", "jianzhong-daoke", "yang-kang",
                "liu-changjie", "dugu-qiubai", "jinlun-fawang", "zuo-lengchan", "gongsun-zhi", "jiangshi-daozhang", "fusang-wushi"});
        object boss;

                while (!fil || !get_object("/kungfu/class/misc/" + fil)->is_character()) {
                        fil = flist[random(sizeof(flist))];
                }
                boss = new("/kungfu/class/misc/" + fil);
                delete("drops", boss);
                boss->move(this_object());

        return 1;
}*/

int do_expel_allusers()//驱逐所有的生物到传送阵，删除他们的startroom，包括水牢里的，无条件释放
{
        object room, me, enemy;
        object *enemies;
        string fil, *flist = get_dir(query("pathstring"));
        int flag;

        me = get_object(__DIR__"teleport");
        if (!objectp(me)) return 0;

        foreach (fil in flist) {
                if (strsrch(fil, "teleport.c") != -1) continue;
                if (strsrch(fil, ".c") == -1) continue;
                room = get_object(query("pathstring") + fil);
                flag = objectp(room);
                if (!flag) continue;
                flag = room->is_room();
                if (!flag) continue;

                enemies = filter_array(deep_inventory(room),
                           (: $1->is_character() &&
                           !owner_level($1)
                           :));

                if (arrayp(enemies) && sizeof(enemies)) foreach (enemy in enemies) {
                        if (strsrch(base_name(enemy), "dongtian") != -1) continue;
                        //if (base_name(enemy)=="/kungfu/class/misc/haigui") continue;
                        //if (base_name(enemy)=="/kungfu/class/misc/shendiao") continue;
                        if (query("env/invisible", enemy)) continue;
                        message_vision(append_color(NOR YEL "虚空中穿过来一只大如山岳的巨掌，对着$N" NOR YEL "拦腰一捞，再缩回去就此不见了。\n" NOR, YEL), enemy);
                        enemy->remove_all_enemy(1);
                        enemy->move(me);
                        enemy->start_busy(3);
                        delete("dongtian/prison/time", enemy);
                        delete("startroom", enemy);
                        enemy->save();
                        message_vision(append_color(NOR YEL "$N" NOR YEL "啪哒一声从天上摔了下来。\n" NOR, YEL), enemy);
                }
        }

        return 1;
}

int place_ldz()
{
        int n = query("lveduo_n");
        int lv, i, j = random(4) + 2;
        object ob;

        add_qy2(n);//梯形累加，最高5000点
        remove_call_out("place_ldz");
        if (query("hold_time") < 2) return 0;

        for( i = 0; i < j; i++ ) {
                n -= 1;
                ob = new(__DIR__"npc/attacker");
                if (!random(4)) lv = random(ATTACKER_LV / 2) + ATTACKER_LV / 2;
                else lv = random(ATTACKER_LV / 3) + ATTACKER_LV / 3;
                lv += ((time() - query("hold_time")) / 86400) * 2;//每天增长2级
                   if (lv > 550) lv = 550;
                set("guarder_level", lv, ob);
                set("nflee", time() + 600, ob);
                ob->do_copyskill();
                ob->move(this_object());
                tell_room(this_object(), NOR HIY " - 掠夺者剩余："+ chinese_number(n) + "个\n" NOR);
                if (n < 1) break;
        }

        if (n > 0) call_out("place_ldz", 30 + random(16));
        set("lveduo_n", n);
        return 1;
}

int do_tick_minute()
{
        object me, ob, enemy;
        object *enemies;
        int addqy, tmpi, i, plv, klj, zlv = query("zhen_type");
        mapping my;
        object own, *owns, where;
        object previous = query("attacker_player");
        int repi, repc, repmax;
        string msg;

        if (!query("flag_init")) reload_object(this_object());

        get_object(__DIR__"zhenbaoge")->add_encounter();
        get_object(__DIR__"cangjingge")->add_encounter();

    delete("attacker_player");
        if (previous && objectp(previous)) {
                previous->set_short_desc(0);
                previous->command("halt");
        }

//有祭祀能量时...start
 if (query("apply/num_jisi")) {
        if (query("hold_time") > 1) {//玩家为主人时，0为无主，1为npc
                        addn("apply/num_jisi_tmp", 1);
                        if (query("apply/num_jisi_tmp") > 2) {
                                set("apply/num_jisi_tmp", 0);
                        addn("apply/num_jisi", -1);
                }
                if ((query("apply/num_jisi") % 10 == 0) || (query("apply/num_jisi") < 1)) {
                        __DIR__"data.c"->do_save("apply/num_jisi", query("apply/num_jisi"));
                }
                if (query("apply/num_jisi") == 1000)
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "魔像饥渴了。\n" + NOR);
                else if (query("apply/num_jisi") == 500)
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "魔像两眼发青。\n" + NOR);
                else if (query("apply/num_jisi") == 100)
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "魔像快要饿死了。\n" + NOR);
        }

        //回复耐久
        if ((repc = query("xiang_life")) < (repmax = query("xiang_maxlife") + query("apply/xiang_maxlife"))) {
                msg = NOR + "魔像轻轻地吸了口气，犹如长鲸吸水，天地元气蜂拥而至。\n ↑.";
                repi = query("apply/xiang_repair") + 1;
               if ( (time() - query("hold_time")) < 86400 * 3 ) repi += 20;
                if ((repc + repi) < repmax) repmax = repc + repi;
                for( i = repc; i < repmax; i++ ) {
                        msg += YEL + to_string(i+1) + NOR + ".";
                }
                msg += ".\n" + NOR;
                addn("xiang_life", repi);
                tell_room(this_object(), msg);
        }

        //傀儡将刷新
        if (!query("born_klj")) {
                klj = query("guarder_pro") / 10;
                if (klj > 5) klj = 5;
                klj = 6 - klj;
                set("born_klj", klj);
                                ob = new(__DIR__"npc/guarder2");
                                set("croom", this_object(), ob);
                                plv = query("guarder_level") / 10;
                                if (plv > 50) plv = 50;
                                if (plv < 20) plv = 20;
                                    if ( (time() - query("hold_time")) < 86400 * 3 )
                                      set("guarder_level", query("guarder_level") + plv + 150, ob);
                                    else
                                set("guarder_level", query("guarder_level") + plv, ob);
                                set("nflee", time() + 120 + random(60) + query("guarder_lifetime") / 2, ob);
                                ob->do_copyskill();
                                set("dtname", dtname, ob);
                                set("name", dtname + query("name", ob), ob);
                                ob->move(this_object());
                        ob->stop_busy();
                        ob->command("exert powerup");
                        ob->stop_busy();
                        ob->command("exert shield");
                        ob->stop_busy();
                        ob->command("exert zu");
                        ob->stop_busy();
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"]   = my["max_jing"];
                        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                        my["qi"]     = my["eff_qi"]     = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                                /*enemy = query("attacker_player");
                                if (enemy && objectp(enemy)) {
                                        if (!query("env/invisible", me)) {
                                                set("enemy_player", enemy, ob);
                                                ob->set_leader(enemy);
                                                ob->kill_ob(enemy);
                                        }
                                } */
                                set("chat_chance", 12, ob);
                                add_ownlist(ob);
        } else {
                addn("born_klj", -1);
        }

        //请雷
                owns = query("ownlist");
                if (!undefinedp(owns) && owns && sizeof(owns)) {
                        foreach (own in owns) {
                                if (!own ||
                                        !objectp(where=environment(own)) ||
                                        (playerp(own) && query("hold_time") != query_temp("dongtian/invite/hold_time", own)) ||
                                        (playerp(own) && !owner_level(own)) /*||
                                        ( (strsrch(base_name(where), query("pathstring")) == -1) && !playerp(own) )*/
                                        ) {
                                                owns -= ({own});
                                                continue;
                                }
                                if (own->is_fighting() && !query_temp("dongtian/smash_step", own)) {
                                enemies = own->query_enemy();
                                if( !enemies || sizeof(enemies) == 0 ) continue;
                                enemy = enemies[random(sizeof(enemies))];
                                        if (playerp(own)) can_smash(own, enemy, 80);
                                        else  can_smash(own, enemy, 90);
                                } else if(!random(10) && !own->is_fighting() &&
                                        (base_name(where)=="/d/city/swing" || base_name(where)=="/d/city/kedian4")) {
                                                addqy = add_qy();
                                                if (addqy) tell_object(own, NOR HIY "你在聊天室发呆为洞天挣得气运 +" + (string)addqy + "\n" NOR);
                                }
                        }
                        set("ownlist",  owns);
                }

        //阵里，可能会有玩家被其他玩家背进去害死
        enemies = filter_array(all_inventory(get_object(__DIR__"enter")),
                           (: playerp($1) &&
                           !owner_level($1)
                           :));
        me = this_object();
        if (arrayp(enemies) && sizeof(enemies)) foreach (enemy in enemies) {
                if (zlv > 0 && random(5) < zlv && !enemy->is_busy()) {
                        tell_object(enemy, NOR "护山大阵猛地一摇，你只有停下了脚步。\n" NOR);
                        enemy->start_busy(1 + random(zlv));
                }
                if (zlv<1) {
                        can_smash(me, enemy, 20);
                }
                else if (zlv<2) {
                        can_smash(me, enemy, 25);
                }
                else if (zlv<3) {
                        can_smash(me, enemy, 30);
                }
                else if (zlv<4) {
                        can_smash(me, enemy, 35);
                }
                else if (zlv<5) {
                        can_smash(me, enemy, 40);
                }
                else {
                        can_smash(me, enemy, 50);
                }
        }

        //恢复大殿和后殿里的主人
        msg = NOR + HBGRN + CYN "徐徐清风吹过，精纯的天地灵气修补了你的身体。\n" + NOR;
        where = get_object(__DIR__"dadian");
        if (where && objectp(where)) {
                enemies = filter_array(all_inventory(where),
                           (: playerp($1) //&&
                           //owner_level($1)
                           :));
                if (arrayp(enemies) && sizeof(enemies)) {foreach (enemy in enemies) {
                        my = enemy->query_entire_dbase();
                        my["jing"]   = my["eff_jing"]   = my["max_jing"];
                        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                        my["qi"]     = my["eff_qi"]     = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                                }
//                              addqy = sizeof(enemies);
//                              if (addqy > 8) addqy = 8;
//                              add_qy2(addqy);
//                              tell_room(where, NOR HIY "洞天气运 +" + (string)addqy + "\n" NOR);
                }
                tell_room(where, msg);
        }
        where = get_object(__DIR__"houdian");
        if (where && objectp(where)) {
                enemies = filter_array(all_inventory(where),
                           (: playerp($1) //&&
                           //owner_level($1)
                           :));
                if (arrayp(enemies) && sizeof(enemies)) {foreach (enemy in enemies) {
                        my = enemy->query_entire_dbase();
                        my["jing"]   = my["eff_jing"]   = my["max_jing"];
                        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                        my["qi"]     = my["eff_qi"]     = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                                }
                }
                tell_room(where, msg);
        }

 }
 //有祭祀能量时...end

        if (query("lveduo_time") && query("lveduo_time") < time()) {
                delete("lveduo_time");
                if (query("hold_time") < 2) {
                        //无条件放弃
                        set("lveduo_wait", time() + 7200);
                }
                else if (query("protect_time") > time()) {
                        //tell_room(this_object(), MAG "听说因为" + dtname + "洞天受到保护，掠夺者们放弃了计划。\n" NOR);
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "据说" + HIC + dtname + "洞天" + NOR + WHT + "因受保护，掠夺者们放弃了计划。\n" NOR);
                        set("lveduo_wait", time() + 7200);
                } else {
                        //开始掠夺
                        //CHANNEL_D->channel_broadcast("debug", NOR + HIW + "洞天福地：掠夺者开始攻击" + dtname + " " + base_name(this_object()) + " \n" + NOR);
                        tell_room(this_object(), NOR CYN "外面护山大阵摇晃不止，数十条蒙面的黑影在林间呼啸，此起彼落地跳跃着从八方拢聚而来。\n" NOR);
                        call_out("place_ldz", 6);
                        set("lveduo_wait", time() + 28800);
                }
        } else if (!query("lveduo_time") && query("lveduo_wait") < time() && !random(350) && (query("hold_time") > 1)) {
                set("lveduo_time", time() + 7200);
                tmpi = random(76) + 25;
                if (tmpi >= 75) msg = "一大帮";
                else if (tmpi >= 50) msg = "一伙儿";
                else msg = "一小撮";
                set("lveduo_n", tmpi);
                //tell_room(this_object(), MAG "听说两小时后，" + msg + "人将图谋对" + dtname + "洞天发起掠夺。\n" NOR);
                CHANNEL_D->channel_broadcast("dt", NOR + HIW + "风传两小时后，" + msg + "人将图谋对" + HIC + dtname + "洞天" + NOR + HIW + "发起掠夺。\n" NOR);
        }

        return 1;

}

int addn_c(int a, int b)
{
        if (a > 0) {
                if (a - b >= 0) return b;
                return a;
        }

        return 0;
}

void addn_p()
{
        int i, num = 1;
        int rnd = random(100);
        int old = chk_zhenlv();
        int flag = 1;
        object *enemies;

        if (query("hold_time") < 2) {//洞天非玩家所属，衰败加2倍
                num *= 3;
        }

        if (rnd < 90 && (i = addn_c(query("guarder_level"), num))) {
                addn("guarder_level", -i);
                __DIR__"data.c"->do_save("guarder_level", query("guarder_level"));
        }
        if (rnd < 32 && (i = addn_c(query("guarder_lifetime"), num))) {
                addn("guarder_lifetime", -i);
                __DIR__"data.c"->do_save("guarder_lifetime", query("guarder_lifetime"));
        }
        if (rnd < 16 && (i = addn_c(query("guarder_pro"), num))) {
                addn("guarder_pro", -i);
                __DIR__"data.c"->do_save("guarder_pro", query("guarder_pro"));
        }
        if (rnd < 5 && (i = addn_c(query("apply/xiang_repair"), num))) {
                addn("apply/xiang_repair", -i);
                __DIR__"data.c"->do_save("apply/xiang_repair", query("apply/xiang_repair"));
        }
        if ( i = addn_c(query("apply/num_yanxi"), num * 3) ) {
                addn("apply/num_yanxi", -i);
                __DIR__"data.c"->do_save("apply/num_yanxi", query("apply/num_yanxi"));
        }

        if (query("hold_time") == 1)//已经是npc所有
        {
                if (query("guarder_level") < 1 && query("guarder_lifetime") < 1 && query("guarder_pro") < 1) {//反弹
                        enemies = filter_array(all_inventory(this_object()),
                           (: playerp($1) &&
                           !query("env/invisible", $1)
                           :));
                        if (arrayp(enemies) && sizeof(enemies)>0) flag = 0;
                        if (flag) {
                                delete("hold_time");
                                set_sys_owner();
                                flag = 2;
                        }
                }
        }
        //chk_zhenlv();//阵图等级降级不？
        if (chk_zhenlv() < old) {
                CHANNEL_D->channel_broadcast("dt",  NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "的护山大阵，跌级为" + query("zhen_lvname") + NOR + WHT + "了。\n" + NOR);
                __DIR__"enter.c"->reload_me();
        } else if (chk_zhenlv() > old)  {
                CHANNEL_D->channel_broadcast("dt",  NOR + WHT + "听说" + HIC + dtname + NOR + WHT + "的护山大阵，升级为" + query("zhen_lvname") + NOR + WHT + "了。\n" + NOR);
                __DIR__"enter.c"->reload_me();
        }

        if (flag == 2) {
                reload_object(this_object());
        }
}

void create3(string na, string pa, string aa)
{
        string msg, fil, ft, *flist;
        object room, eroom, oroom;
        object *enemies;
        int flag = 1;

        if (!query("flag_init")) reload_object(this_object());
        //CHANNEL_D->channel_broadcast("debug", NOR + HIG + "na:"+ na + "  pa:" + pa + "\n" + NOR);

        eroom = get_object(__DIR__"enter");
        if (!objectp(eroom)) return;//没有大阵
        //if (stringp(query("exits/out", eroom)) && query("hold_time") > 1) return;//大阵已经创建，并且属于玩家洞天
        flist = get_dir(pa);

        while (flag) {
                if (!sizeof(flist)) break;
                ft = flist[random(sizeof(flist))];
                flist -= ({ft});
                fil = pa + ft;
                if (strsrch(fil, ".c") == -1) continue;
                if (!objectp(room = get_object(fil))) continue;
                if (!room->is_room()) continue;
                flag = 0;
        }
        //CHANNEL_D->channel_broadcast("debug", NOR + HIG + "basename:" + base_name(room) + "\n" + NOR);

        if ( stringp(query("exits/out", eroom)) && objectp(oroom = get_object(query("exits/out", eroom))) ) {
                tell_room(oroom, NOR HIB "只见空间扭曲，通往" + dtname + "洞天的阵门已经合上了。\n" NOR);
                delete("exits/dongtian", oroom);
        }

        __DIR__"data.c"->do_save2("outroom", base_name(room));

        if (!query("flag_init", eroom)) reload_object(eroom);
        else {
                eroom->create_exit2();
        }

        if (na && query("hold_time") < 2) {//洞天非玩家所属，并且没有人闯阵时
                flag = 1;
                enemies = filter_array(all_inventory(eroom),
                           (: playerp($1) &&
                           !query("env/invisible", $1)
                           :));
                if (arrayp(enemies) && sizeof(enemies)>0) flag = 0;
                enemies = filter_array(all_inventory(this_object()),
                           (: playerp($1) &&
                           !query("env/invisible", $1)
                           :));
                if (arrayp(enemies) && sizeof(enemies)>0) flag = 0;
                if (flag) {
                        log_file("static/dongtian", "  -( 无人闯入之NPC洞天更名重载 )\n");
                        save_name(na);
                        reload_object(eroom);
                }
        }

        CHANNEL_D->channel_broadcast("news", NOR + HIG + "传说" + HIC + dtname + "洞天" + HIG + "在" + aa + "现世。\n" NOR);
        //CHANNEL_D->channel_broadcast("debug", NOR + HIW + "洞天福地：在 " + base_name(room) + " 创建了通往" + dtname + "洞天的dongtian入口。\n" + NOR);
}

int create2(string na, string pa, string aa)
{
        call_out("create3", 3, na,pa,aa);
        return 1;
}

void cg_add(object me)
{
        mapping students = __DIR__"data.c"->do_load2("students");
        if (undefinedp(students) || !students)
                students = ([]);
        students[query("id", me)] = query("hold_time");
        __DIR__"data.c"->do_save2("students",students);
}

void cg_remove(object me)
{
        mapping students = __DIR__"data.c"->do_load2("students");
        if (undefinedp(students) || !students)
                return;
        map_delete(students, query("id", me));
        __DIR__"data.c"->do_save2("students",students);
}

void cg_check()
{
        object student;
        string sid, hu = "/d/dongtian/obj/baiyuhu.c";
        int sguid;
        mapping students = __DIR__"data.c"->do_load2("students");

        //DEBUG_CHANNEL(1);
        if (undefinedp(students) || !students || !sizeof(students))
                return;
        sid = keys(students)[random(sizeof(students))];//抽查一人
        sguid = students[sid];
        if (sguid) {
                student = find_player(sid);
                if (!student || !playerp(student))
                        return;
                if (sguid = hu->is_learned(student)) {
                        if (sguid!=query("hold_time")) hu->fangqiall(student);
                }
        }
}

int query_dt_qy()
{
        int qy;
        qy = query("dt_qy");
        if (undefinedp(qy) || !qy)
                qy = __DIR__"data.c"->do_load("qy");
        if (undefinedp(qy) || !qy) {
                qy = 1;
                set("dt_qy", qy);
        }
        return qy;
}

int add_qy()
{
        int qyn, qy;
        if (query("dt_qy_addtime") > time()) return 0;
        //DEBUG_CHANNEL(NOR + base_name(this_object()) + " qy + 1\n" + NOR);
        qyn = random(5)+1;
        qy = query_dt_qy();
        set("dt_qy_addtime", time() + 15);//至少15秒
        qy += qyn;
        set("dt_qy", qy);
        __DIR__"data.c"->do_save("qy", qy);
        return qyn;
}

int add_qy2(int addnum)
{
        int qy = query_dt_qy();
        qy += addnum;
        set("dt_qy", qy);
        __DIR__"data.c"->do_save("qy", qy);
        return qy;
}

int count_qy()
{
        object ob, room = get_object(__DIR__"houdian.c");
        int qy = query_dt_qy();
        int giftnum = query("dt_qy_giftnum");

        if (undefinedp(giftnum) || !giftnum)
                giftnum = __DIR__"data.c"->do_load("giftnum");
        if (undefinedp(giftnum) || !giftnum) {
                giftnum = 1;
        }

        //普通最佳情况下，每天不过3500点气运，等于3天可在此抽一次。
        //屠人场的傀儡将被杀的情况下，就凑不足10000点气运
        //白玉笏直接返点20000，等于直接给2次抽取机会
        if ((qy / 10000) >= giftnum) {
                giftnum += 1;

                if (!random(6)) {
                        ob = new("/u/redl/npc/obj/ntb");
                        log_file("static/yangyong3",sprintf("%s 洞天 10000气运 -> 百元泥潭币, 主人( %s )\n",TIME_D->replace_ctime(time()), implode(query("owners"), "、")));
                }
                else ob = EQUIPMENT_D->create_dynamic("", 60, 600);
                CHANNEL_D->channel_broadcast("dt", NOR + HIW + "传说" + HIC + load_name() + "洞天" + NOR + HIW +
                         "秉承天地气运，后殿的功德池内结出了" +  query("name", ob) + NOR + HIW + "。\n" + NOR);
                ob->move(room);
                set("who_get/id", "redl", ob);
                set("who_get/time", time() + 180, ob);//3分钟内谁也不能捡起
                tell_room(room, NOR + "功德池内气运莲花冉冉盛开，其中一朵托起" + query("name", ob) + NOR + "后一振抛在地上。\n" + NOR);
        }

        set("dt_qy_giftnum", giftnum);
        __DIR__"data.c"->do_save("giftnum", giftnum);
        return 1;
}

void heart_beat()
{
        object ob;
        string roompath, roomname;
        int plv;
        mapping my;

        do_tick_minute();
        if (query("addn_p_minute") < time()) {
                set("addn_p_minute", time() + 3200);
                //随机降低属性
                addn_p();
                cg_check();
        }
        if (query("count_qy_minute") < time() && query("hold_time") > 1) {
                set("count_qy_minute", time() + 300);
                count_qy();
        }

        if (query("qybattle_minute") < time() && query("hold_time") > 1) {
                set("qybattle_minute", time() + 28800);

                                ob = new(__DIR__"npc/guarder2");
                                set("croom", this_object(), ob);
                                plv = query("guarder_level") / 10;
                                if (plv > 50) plv = 50;
                                if (plv < 20) plv = 20;
                                set("guarder_level", (query("guarder_level") + plv) * 2/3, ob);
                                set("nflee", time() + 600 + random(30) + query("guarder_lifetime") * 3, ob);
                                ob->do_copyskill();
                                set("dtname", dtname, ob);
                                set("name", dtname + query("name", ob), ob);
                                roompath = "/d/pk/turen" + (string)(1 + random(12));
                                //DEBUG_CHANNEL((string)query_dt_qy() + " - " + roompath);
                                ob->move(roompath);
                                roomname = query("short", environment(ob));
                                CHANNEL_D->channel_broadcast("dt", NOR + WHT + query("name", ob) + NOR + WHT + "：秉承洞天气运( " + (string)query_dt_qy() + " )点在" + roomname + NOR + WHT + "接受挑战。\n" + NOR);
                        ob->stop_busy();
                        ob->command("exert powerup");
                        ob->stop_busy();
                        ob->command("exert shield");
                        ob->stop_busy();
                        ob->command("exert zu");
                        ob->stop_busy();
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"]   = my["max_jing"];
                        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                        my["qi"]     = my["eff_qi"]     = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                                set("chat_chance", 3, ob);
                                add_ownlist(ob);
        }

        if (random(2)) set_heart_beat(41);
                else set_heart_beat(37);

}
