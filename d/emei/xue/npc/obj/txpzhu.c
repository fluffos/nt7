// This program is a part of NITAN MudLIB 
// redl 2014
// 宝物
#include <armor.h>
#include <ansi.h>
#include <combat.h>
//inherit ITEM;
inherit F_CLEAN_UP;
inherit MYHEART;

int not_force(object ob);

int query_autoload() { return 0; }

int is_artifacts() { return 1; }
int is_xpzhu() { return 1; }

void create()
{
                set_name(NOR HIG "玄牝" HIR "珠" NOR , ({ "xuanpin zhu", "zhu" }));
                        set_weight(10);
                set("unit", "颗");
                set("value", 100);
                set("material", "no name");
                set("material_file", "/clone/goods/noname");
                set("no_uget", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("no_sell", 1);
                set("no_pawn", 1);
                                set("quality_level", 6);
                set("unique", 1);

//凝练后
//                 set("no_give", 1);
//                 set("no_get", 1);
//                 set("no_drop", 1);

                                set("wear_msg", NOR CYN "$N" NOR CYN "从怀里掏出一颗绿莹莹的$n" NOR CYN "往天上一抛。\n"); 
                                
                                set("no_wear",  NOR "玄牝珠不用装备，凝练后直接使用(use xuanpin zhu)它。\n" NOR );
                                set_temp("no_wear",  NOR "玄牝珠不用装备，凝练后直接使用(use xuanpin zhu)它。\n" NOR );
                                
//                              set_heart_beat(3);
                                set("set_data", 1); 
                                set("auto_load", 1); 
                        setup();
}        

void create2(object me)
{
                int i = 0, lv = 9;
        while (i++ < 8) { 
                        if (random(i*i) == 0 ) { 
                                lv += 1;
            } else 
                                break; 
                } 
                set("ob_lv", lv);
                set("armor_prop/add_skill", lv*lv*lv/5);
        set("armor_prop/max_qi", lv * 500000); 
        set("armor_prop/max_jing", lv * 250000); 
        set("long", HIC "百蛮山的绿袍老祖利用玄牝大法所炼法宝。\n"
                                        "可凝练(ninglian xuanpin zhu)第二元神，它天生(" + HIY + (string)lv + HIC + ")孔。\n"
                                        "具有把宝石等镶嵌物多倍增益的效果，是第二元神的装备倚仗。\n"
                            HIK "(在屠人场凝练测试效果，在其余地方凝练永久固化。\n"
                                " 无法丢弃，一旦镶嵌就无法熔炼。\n"
                                " 凝练后只能dest xuanpin zhu来永久销毁。)\n" NOR);
        set("enchase/flute", lv);
        this_object()->move(me, 1);
}

string *cant_force_path = ({
        "/adm/",
        "/data/",
        "/kungfu/class/",
        "/u/",
        "/quest/",
        "/city2/meng/",//kw
        "/dongtian/",
        "/linggt/",
});
string *can_fang_path = ({
        "/d/pk/",
//      "/u/",
//      "/d/",
});

int back_fan(object me, object fan)
{
        if (!fan || !me)
                return 1;
        if( environment(me)!=environment(fan))
                return 1;
        message_vision(append_color(NOR YEL "\n$N" NOR YEL "轻轻一招手，八十一杆" + query("name", fan) + NOR + YEL + "纷纷飞回囊中。\n\n" NOR, YEL), me);
        fan->move(me, 1);
        return 1;
}

int stop_making(object me)
{
        delete_temp("jsfan/fan", me);
        delete_temp("jsfan/target", me);
        delete_temp("jsfan/making", me);
        me->set_short_desc(0);
        me->start_busy(4);
        return 0;
}

int making(object me)
{
        string msg;
        object target = query_temp("jsfan/target", me);
        object fan = query_temp("jsfan/fan", me);
        int i, oblv = query("ob_lv", fan), damage;
        mapping fclists;

        if( !fan || environment(me)!=environment(fan))
        {
                write("咦？你的旗子呢，地上的旗子跑哪儿去了...\n");
                return stop_making(me);
        }
        
        if( !target || !objectp(target) || environment(me)!=environment(target))
        {
                //write("咦？对方跑哪儿去了...\n");
                back_fan(me, fan);
                return stop_making(me);
        }

        if (query_temp("jsfan/making", me)>27) set_temp("jsfan/making", 27, me);//免溢出
        msg = CYN + "\n" + query("name", fan) + NOR + CYN + (random(2) ? "急" : "一") +  (random(2) ? "抖" : "振") + "，放出" + chinese_number(3 * query_temp("jsfan/making", me)) + "条玄阴煞气卷向$n，";
        if (target->is_busy() || oblv > random(20) || (query("level", target)<20 && query("combat_exp", target)<100000000)) {
                msg += "$n" + NOR + CYN +  (random(2) ? "神情" : "魂魄") +  (random(2) ? "恍惚" : "呆滞") + "。\n" + NOR;
                message_vision(NOR + msg + NOR, me, target);
                addn_temp("jsfan/making", 1, me);
                damage = pow((oblv + 25), 2) * pow(3, query_temp("jsfan/making", me)-8);
                damage = damage * 9 / 10 + random(damage / 10);
                target->receive_damage("jing", damage, me);
                msg = NOR + HIW + "( $N" + NOR + HIW + "的" + query("name", fan) + NOR + HIW + "对$n" + NOR + HIW + "的精造成"+ damage + "点伤害。)\n" + NOR;
                message_vision(NOR + msg + NOR, me, target);
                COMBAT_D->report_status(target);
                if (random(me->query_kar()) > 8) {
                        addn_temp("jsfan/making", 1, me);
                        tell_object( me, HIY "你福至心灵，勾动" + query("name", fan) + NOR + HIY + "的煞气再度进击..\n" NOR);
                        damage *= 2;
                        target->receive_damage("jing", damage, me);
                        msg = NOR + HIW + "( $N" + NOR + HIW + "的" + query("name", fan) + NOR + HIW + "对$n" + NOR + HIW + "的精造成"+ damage + "点伤害。)\n" + NOR;
                        message_vision(NOR + msg + NOR, me, target);
                        COMBAT_D->report_status(target);
                        if (random(me->query_kar()) > 24) {
                                addn_temp("jsfan/making", 1, me);
                                tell_object( me, HIY "你福至心灵，勾动" + query("name", fan) + NOR + HIY + "的煞气再度进击..\n" NOR);
                                damage *= 2;
                                target->receive_damage("jing", damage, me);
                                msg = NOR + HIW + "( $N" + NOR + HIW + "的" + query("name", fan) + NOR + HIW + "对$n" + NOR + HIW + "的精造成"+ damage + "点伤害。)\n" + NOR;
                                message_vision(NOR + msg + NOR, me, target);
                                COMBAT_D->report_status(target);
                        }
                }
                
                if (query("jing", target) < 1) {
                        if (target->is_boss() || playerp(target)) {
                                        write(NOR "你无法收摄" + query("name", target) + NOR + "的生魂。\n" NOR);
                                } else {        
                        message_vision(NOR + YEL + "\n只见$n" + NOR + YEL + "凄声大吼，一点真灵从头上幽幽冒起...\n“倏”地被收入了$N" + NOR + YEL + "的" + 
                                                                                                                     query("name", fan) + NOR + YEL + "，化为幡上的一尊鬼脸。\n\n" + NOR, me, target);
                        fclists = query("fc_list", fan);
                        if (!fclists) {
                                fclists = ([base_name(target) : 1]);
                    } else if ( !fclists[base_name(target)] ) {
                                fclists += ([base_name(target) : 1]);
                    } else {
                                fclists[base_name(target)] += 1;
                        }
                        set("fc_list", fclists, fan);
                }
                //set("jing", -999999999, target);
                //set("eff_jing", -999999999, target);
                target->die(me);
                back_fan(me, fan);
                return stop_making(me);
                }
        } else {
                msg += "$n" + NOR + CYN +  (random(2) ? "凝神" : "静心") +  (random(2) ? "避开" : "躲过") + "。\n";
                message_vision(NOR + msg + NOR, me, target);
        }
        return 1;                       
}

int halt_make(object me)
{
        back_fan(me, query_temp("jsfan/fan", me));
        stop_making(me);
        return 1;
}

int not_force(object ob)
{
        int idx;
        string basename;
/*      if (ob->is_boss()) {
                write(NOR "对方神念过于强大。\n" NOR);
                return 1;
        }*/
        if (query("no_jushoufan", ob)) {
                write(NOR "对方是受保护的。\n" NOR);
                return 1;
        }
        idx = sizeof(cant_force_path);
        basename = base_name(ob);
        while (idx--) {
                if ( strsrch(basename, cant_force_path[idx])!=-1 ) {
                        write(NOR "对方有特殊身份。\n" NOR);
                        return 1;
                }
        }
        return 0;
}
int can_fang(object room)
{
        int idx;
        string basename;
        idx = sizeof(can_fang_path);
        basename = base_name(room);
        while (idx--) {
                if ( strsrch(basename, can_fang_path[idx])!=-1 ) {
                        return 1;
                }
        }
        return 0;
}

int do_shou(string arg)
{
        mapping fclists;
        object *enemies, room, target, me = this_player();
        
        if( environment()!= me ) {
                write(NOR "你身上有" + query("name") + NOR + "吗？\n" NOR);
                return 1;
        }
        if (me->is_busy()) {
                write(NOR "你正在忙着呢。\n" NOR);
                return 1;
        }
        if (!query("equipped")) {
                write(NOR "你需要先把" + query("name") + NOR + "装备好。\n" NOR);
                return 1;
        }
        if (!arg || arg=="" || sscanf(arg, "%s", arg)!=1) {
                write(NOR "你想拿" + query("name") + NOR + "去收谁？\n" NOR);
                return 1;
        }
        room = environment(me);
        if (!room || !room->is_room() || query("no_fight", room) || query("no_magic", room)) {
                write(NOR "你不能在这里捣乱。\n" NOR);
                return 1;
        }
        me->start_busy(2);
        target = present(arg, room);
        if (!target || !target->is_character()) {// || !living(target)) {
                write(NOR "你看清楚那是什么东西？\n" NOR);
                return 1;
        }
        /*if (playerp(target)) {
                write(NOR "你不能搞玩家。\n" NOR);
                return 1;
        }*/
        if (target->is_baby()) {
                write(NOR "你没听过“祸不及妻儿”？\n" NOR);
                return 1;
        }
        if (not_force(target)) {
                write(NOR "你无法收摄" + query("name", target) + NOR + "的生魂。\n" NOR);
                return 1;
        }
        fclists = query("fc_list");
        if (fclists && sizeof(fclists) > 5) {
                write(NOR "你收摄在" + query("name") + NOR + "上的生魂种类太多了。\n" NOR);
                return 1;
        }
        if (living(target)) {
                enemies = me->query_enemy();    
                if (!enemies || !arrayp(enemies) || !sizeof(enemies) || member_array(target, enemies) == -1) {
                        write(NOR "你和" + query("name", target) + NOR + "目前没有战斗。\n" NOR);
                        return 1;
                }
        }
        this_object()->unequip();
        this_object()->move(room, 1);
        set("who_get/id", query("id", me));
        set("who_get/time", time() + 120);
        set_temp("jsfan/target", target, me);
        set_temp("jsfan/fan", this_object(), me);
        set_temp("jsfan/making", 9, me);
        message_vision(append_color(NOR YEL "\n$N" NOR YEL "一扬手，八十一杆" + query("name") + NOR + YEL + "齐齐飞出，插在$n" + NOR + YEL + "周围的地上。\n\n" NOR, YEL), me, target);
        me->start_busy((:call_other, __FILE__, "making", me :),
                       (:call_other, __FILE__, "halt_make", me :));
        me->set_short_desc("正在收摄" + query("name", target) + NOR + "的魂魄。");
        return 1;
}

int dest_fang2(object target)
{
        if (!target) return 1;
        if (!objectp(target)) return 1;
        destruct(target);
        return 1;
}

int dest_fang(object target)
{
        call_out("dest_fang2", 60, target);
        return 1;
}

int do_fang()
{
        mapping fclists;
        object ob, *obs, ene, *enemies = ({}), room, target, me = this_player();
        int idx, num, max = 8 + random(5);
        string objfile, msg = NOR + YEL + "\n$N" + NOR + YEL + "一扬手，" + query("name") + NOR + YEL + "上阴气滚滚，杀出来一群凶灵..." + NOR;
        
        if( environment()!= me ) {
                write(NOR "你身上有" + query("name") + NOR + "吗？\n" NOR);
                return 1;
        }
        if (me->is_busy()) {
                write(NOR "你正在忙着呢。\n" NOR);
                return 1;
        }
        if (!query("equipped")) {
                write(NOR "你需要先把" + query("name") + NOR + "装备好。\n" NOR);
                return 1;
        }
        me->start_busy(2);
        room = environment(me);
        if (!room || !room->is_room() || !can_fang(room)) {
                write(NOR "这里不是能释放凶灵的地方。\n" NOR);
                return 1;
        }
        obs = filter_array(all_inventory(room), (: $1->is_character() :));
        if (obs && arrayp(obs) && sizeof(obs)>=10) {
                write(NOR "这里干扰的魂魄太多了。\n" NOR);
                return 1;
        }

        fclists = query("fc_list");
        if (fclists && (idx = sizeof(fclists))) {
                while (max-- && (idx = sizeof(fclists))) {
                        idx = random(idx);
                        objfile = keys(fclists)[idx];
                        num = fclists[objfile];
                        if (num) {
                                target = new(objfile);
                                target->set_name( query("name", target) + HIB "的凶灵" NOR, ({ "xiong ling", "ling" }));
                                //set("title", HIB "凶灵" NOR);
                                set("own_ob_jushouxiongling", me, target);
                        set("gift/exp", query("gift/exp", target)/2, target);//尽量减少喂经验奖励的漏洞
                        set("gift/pot", query("gift/pot", target)/2, target);
                        set("gift/mar", query("gift/mar", target)/2, target);
                                //msg += query("name", target) + NOR;
                                enemies += ({target});
                                fclists[objfile] = num -1;
                                call_other( __FILE__, "dest_fang", target);
                        }
                        if (num <= 1) {
                                map_delete(fclists, objfile);
                        }
                        
                }
                set("fc_list", fclists);
                message_vision(msg + NOR + YEL + "。\n\n" + NOR, me);
                enemies->move(room, 1);
        foreach(ob in obs) {
                if ( ob==me || query("own_ob_jushouxiongling", ob)==me ) continue;
                enemies->kill_ob(ob);
                foreach(ene in enemies) ob->kill_ob(ene);
        }
        me->start_busy(6) + random(2);
                return 1;
        } else {
                write(NOR + query("name") + NOR + "上已经没有生魂了。\n" NOR);
                return 1;
        }


        return 1;
}

void init()
{
        if (!this_player()->is_character()) return;
        add_action("do_shou", ({"shou"}));  
        add_action("do_fang", ({"fang"}));  
}



