// This program is a part of NT MudLIB
// moduled.c
// 修改支持同时穿多个套装 by lonely

/*
// 自造装备套装数据格式
<1>
<mod_name>$HIC$大道$NOR$</mod_name>
<bas>5</bas>
<num>12</num>
<bas_prop>
add_busy:5
add_weak:5
reduce_busy:5
avoid_weak:5
</bas_prop>
<adv_prop>
avoid_locked:5
add_damage:20
add_skill:50
avoid_busy:5
counter_damage:20
add_locked:5
reduce_damage:5
</adv_prop>
</1>

// 非自造装备套装格式...
<M3000>
<mod_name>$CYNGRN$龙之神力$NOR$</mod_name>
<mod_parts>
A3000:$CYNGRN$龙之护腕$NOR$
A3001:$CYNGRN$龙神鳞甲$NOR$
A3002:$CYNGRN$龙神披风$NOR$
A3003:$CYNGRN$龙之束带$NOR$
A3004:$CYNGRN$恶龙之触$NOR$
A3005:$CYNGRN$龙骨胫甲$NOR$
A3006:$CYNGRN$龙骨战衣$NOR$
</mod_parts>
<bas>3</bas>
<num>6</num>
<bas_prop>
avoid_locked:20
add_locked:20
add_busy:10
</bas_prop>
<adv_prop>
reduce_busy:20
avoid_busy:20
add_weak:10
avoid_weak:20
add_damage:20
reduce_damage:20
</adv_prop>
</M3000>

// 非自造套装部件格式...
<A3002>
<type>armor/surcoat</type>
<name>$CYNGRN$龙神披风$NOR$</name>
<id>dragon surcoat</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龙之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>2</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:10
apply_prop/str:2
apply_prop/dex:1
apply_prop/dodge:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:10
apply_prop/str:2
[/1]
[2]
id:magic stone
name:灵石
apply_prop/dex:1
apply_prop/dodge:1
[/2]
</insert>
</A3002>
*/

#include <ansi.h>
inherit F_DBASE;

#define EQUIP_LIST      CONFIG_DIR "equiplist/"
#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "套装精灵："+(string)x)

class eqmodule
{
        string mod_level;       // 套装序号 作为序引读取资料
        string mod_name;        // 套装名称
        mapping mod_parts;      // 套装组件名称
        int bas;                // 套装激活基本属性数量
        int num;                // 套装组件数量
        mapping bas_prop;       // 套装组合基本属性
        mapping adv_prop;       // 套装组合高级属性
        //mapping add_prop;       // 套装组合补充属性，套装属性应该是bas_prop+adv_prop+add_prop
}

class eqmodule load_module(string modlevel);
nosave mixed all = ([]);
string module_stats(object obj, object owner);
int valid_module(class eqmodule mod_stats);
void equip_module(object ob, object owner);
void unequip_module(object ob, object owner);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "套装精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "套装系统已经启动。");
}

// 根据套装部件和持有部件者打印部件信息,应用于look.c调用
string module_stats(object ob, object owner)
{
        class eqmodule mod_stats;
        string modlevel, modname, *apply, *eq_files, *key;
        mapping modparts, data;
        mapping stats;
        int i, j, n, bas, num, len = 0;
        string msg, str, eq_str;

        // 初始化资料
        msg = "";
        modlevel = query("mod_level", ob);
        modname = query("mod_name", ob);

        if( classp(query_temp("module/"+modlevel+"_"+modname, owner)) )
        {
                mod_stats = query_temp("module/"+modlevel+"_"+modname, owner);
        }
        else
        {
                if( undefinedp(all[modlevel]) )
                        mod_stats = load_module(modlevel);
                else
                        mod_stats = copy(all[modlevel]);
        }

        // 检查合法性
        if( valid_module(mod_stats) )
        {
                num = mod_stats->num;   // 套装部件数量
                // 激活的自造套装部件或掉落的套装部件
                if( query_temp("module/"+modlevel+"_"+modname, owner) || !ob->is_item_make() )
                        modparts = mod_stats->mod_parts;

                // 自造未激活套装部件
                else
                        modparts = query_temp("module/modparts_" + modlevel+"_"+modname, owner);

                if( !mapp(modparts) ) modparts = ([]);
                apply = keys(modparts);

                msg = sprintf(HIW"  %s(%d/%d"NOR")\n",
                               modname,
                               query_temp("module/modamount_"+modlevel+"_"+modname, owner), num);
                msg+= sprintf(NOR "┏--------------------┓\n");

                data = query_temp("module/modparts_" + modlevel+"_"+modname, owner);
                if( !mapp(data) ) data = ([]);
                eq_files = keys(data);

                for( i=0;i<sizeof(apply);i++ )
                {
                        eq_str = "  ";

                        if( member_array(apply[i], eq_files) != -1 )
                                eq_str = WHT "√" NOR;

                        if( query("mod_mark", ob) == apply[i] )
                                if( query_temp("mod_equip", ob) )
                                        eq_str = HIR"√"NOR;
                                else
                                        eq_str = RED"×"NOR;

                        str = sprintf(NOR "┃%s%-18s"NOR"┃\n",eq_str, modparts[apply[i]]);
                        msg += str;
                }
                if( ob->is_item_make() && member_array(query("mod_mark", ob), apply) == -1 )
                {
                        eq_str = RED"×"NOR;
                        str = sprintf(NOR "┃%s%-18s"NOR"┃\n",eq_str, ob->name(1));
                        msg += str;
                }

                msg += sprintf(NOR "┗--------------------┛\n");
                bas = mod_stats->bas;
                if( query_temp("module/modamount_"+modlevel+"_"+modname, owner) >= bas )
                        eq_str = HIR;
                else
                        eq_str = HIK;
                //msg += sprintf(HIG"  装备效果"NOR")\n");
                msg += sprintf(NOR "%s┏--------------------┓"NOR"\n", eq_str);

                str = sprintf("%d件:", bas);
                msg += sprintf(NOR "%s┃"NOR"%-20s%s┃"NOR"\n", eq_str, str, eq_str);
                stats = copy(mod_stats->bas_prop);
                key = keys(stats);
                if( sizeof(key) > 0 )
                {
                        for( i=0;i<sizeof(key);i++ )
                        {
                                str = EQUIPMENT_D->chinese(key[i], stats[key[i]]);
                                str = HIG + str + NOR;
#ifndef LONELY_IMPROVED
                                len = color_len(str);
#endif
                                msg += sprintf(NOR "%s┃"NOR"%-" + (20 + len) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                        }
                }
                if( query_temp("module/modamount_"+modlevel+"_"+modname, owner) == num )
                        eq_str = HIR;
                else
                        eq_str = HIK;
                str = sprintf("%d件:", num);
                msg += sprintf(NOR "%s┃"NOR"%-20s%s┃"NOR"\n", eq_str, str, eq_str);
                stats = copy(mod_stats->adv_prop);
                key = keys(stats);
                if( sizeof(key) > 0 )
                {
                        for( i=0;i<sizeof(key);i++ )
                        {
                                str = EQUIPMENT_D->chinese(key[i], stats[key[i]]);
                                str = HIG + str + NOR;
#ifndef LONELY_IMPROVED
                                len = color_len(str);
#endif
                                msg += sprintf(NOR "%s┃"NOR"%-" + (20 + len) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                        }
                }


                msg += sprintf(NOR "%s┗--------------------┛"NOR"\n", eq_str);
        }
        return msg;
}

// 根据检查一个套装是否合法，即是否存在，如果套装数据还是初始化数据，就是不存在。
int valid_module(class eqmodule mod_stats)
{
        if( mod_stats->mod_level == "" )
                return 0;

        if( mod_stats->mod_name == "" )
                return 0;
        /*
        if( !(mod_stats->mod_parts) )
                return 0;

        if( !(mod_stats->bas_prop) )
                return 0;

        if( !(mod_stats->adv_prop) )
                return 0;

        if( !(mod_stats->add_prop) )
                return 0;
        */
        return 1;
}

// 根据序号查找套装数据
class eqmodule load_module(string modlevel)
{
        string filename, this_file, temp_str;
        object ob;
        class eqmodule item;
        string *field;
        string modname, names, bas_prop, adv_prop;
        int i, bas, num;
        mapping stats;
        string key;
        mixed value;

        if( modlevel[0] == 'M' )
        {
                if ( modlevel[1] == '0' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"basic.mod";
                else if ( modlevel[1] == '1' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"advance.mod";
                else if ( modlevel[1] == '2' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"expert.mod";
                else if ( modlevel[1] == '3' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"boss.mod";
        }
        else if( modlevel == "1" || modlevel == "2" || modlevel == "3" || modlevel == "4" )
        {
                // 玩家自造装备套装化
                filename = EQUIP_LIST + "ultra.mod";
        }

        // 初始化一个空的套装文件
        item = new(class eqmodule);
        item->mod_level = "";
        item->mod_name = "";
        item->mod_parts = ([]);
        //item->add_prop = ([]); // 装备部件增加的套装属性

        // 文件为空。返回空值。
        if( !stringp(filename) || file_size(filename) < 0 )
                return item;

        this_file = read_file(filename);

        // 根据套装序号查找序号所在文件表，查找匹配套装数据
        sscanf( this_file, "%*s<"+modlevel+">%s</"+modlevel+">%*s", temp_str);
        sscanf( temp_str, "%*s<mod_name>%s</mod_name>%*s", modname);
        sscanf( temp_str, "%*s<mod_parts>\n%s\n</mod_parts>%*s", names);
        sscanf( temp_str, "%*s<bas>%d</bas>%*s", bas);
        sscanf( temp_str, "%*s<num>%d</num>%*s", num);
        sscanf( temp_str, "%*s<bas_prop>\n%s\n</bas_prop>%*s", bas_prop);
        sscanf( temp_str, "%*s<adv_prop>\n%s\n</adv_prop>%*s", adv_prop);

        item->mod_level = modlevel;
        item->mod_name = trans_color(modname, 3); // 转换颜色

        if( bas ) item->bas = bas;
        if( num ) item->num = num;

        // 解析属性表，填入属性关键字和套装属性。
        if (bas_prop != "")
        {
                stats = ([]);
                field = explode(bas_prop, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        if( sscanf( field[i], "%s:%d", key, value ) != 2 )
                            sscanf( field[i], "%s:%s", key, value );
                        // 无需复杂的解析
                        stats[key] = value;
                }
                item->bas_prop = copy(stats);
        }

        if (adv_prop != "")
        {
                stats = ([]);
                field = explode(adv_prop, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        if( sscanf( field[i], "%s:%d", key, value ) != 2 )
                            sscanf( field[i], "%s:%s", key, value );
                        // 无需复杂的解析
                        stats[key] = value;
                }
                item->adv_prop = copy(stats);
        }

        // 解析文件表，填入文件名称和套装部件中文名字。
        if( sizeof(names) )
        {
                stats = ([]);
                field = explode(names, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        field[i] = trans_color(field[i], 3); // 转换颜色
                        sscanf( field[i], "%s:%s", key, value );
                        stats[key] = value;
                }
                item->mod_parts = copy(stats);
        }

        if( !all ) all = ([]);
        all[modlevel] = copy(item);
        return item;
}

// 装备套装部件
// ob套装部件 owner装备者
void equip_module(object ob, object owner)
{
        class eqmodule mod_stats;
        class eqmodule tmp_stats;
        mapping data, stats, applied_prop;
        mapping modparts;
        string *apply;
        string modname;
        string modlevel, file, name;
        object *inv, *obs;
        int i, n;
        int bas, num;
        int max_qi, max_jing;

        if( ob->is_item_make() )
        {
                // 自造装备非装备主人无法激活套装属性
                if( ob->item_owner() != query("id", owner) )
                        return;
        }

        modlevel = query("mod_level", ob); // 套装的序号、等级
        modname = query("mod_name", ob);   // modname 来判断是否是套装

        inv = owner->query_equipment_objects(); // 优化效率
        if( ob->is_item_make() )        // 检查套装部件
        {
                obs = filter_array(inv,
                        (: query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) &&
                           $1->is_item_make() && $1->item_owner() == $(query("id", owner)) :));
        }
        else
                obs = filter_array(inv,
                        (: query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) && !$1->is_item_make() :));

        n = sizeof(obs); // 装备的套装件数

        // 自造的绿化的时候用base_name作为mark，掉落的用部件序号作为mark
        file = query("mod_mark", ob);
        name = query("name", ob);

        // 标记套装组件
        modparts=query_temp("module/modparts_"+modlevel+"_"+modname, owner);
        if( !mapp(modparts) || !sizeof(modparts) ) modparts = ([]);
        modparts[file] = name;
        set_temp("module/modparts_"+modlevel+"_"+modname, modparts, owner);

        // 标记套装件数
        addn_temp("module/modamount_"+modlevel+"_"+modname, 1, owner);

        // 装备的套装设置标记
        set_temp("mod_equip", 1, ob);

        // 少于2件不成套装
        if( n < 2 ) return;

        // 读取套装资料
        if( undefinedp(all[modlevel]) )
                mod_stats = load_module(modlevel);
        else
                mod_stats = copy(all[modlevel]);

        // 检查合法性
        //if( !valid_module(mod_stats) )
        //        return;

        bas = mod_stats->bas;
        num = mod_stats->num;

        if( n < bas ) return; // 小于最少激活套装数量，无法激活套装属性
        else if( n == bas )
        {
                // 加上正在装备的ob，正好激活套装属性
                mod_stats->mod_name = modname;
                if( ob->is_item_make() )        // 补充套装的部件资料
                        mod_stats->mod_parts = ([ file : name ]);

                set_temp("mod_active", 1, ob);  // look时候颜色变化

                for( i=0; i<n; i++ ) {
                        if( ob->is_item_make() ) // 补充自造套装部件资料
                        {
                                data = copy(mod_stats->mod_parts);
                                data[query("mod_mark", obs[i])] = obs[i]->name(1);
                                mod_stats->mod_parts = copy(data);
                        }

                        set_temp("mod_active", 1, obs[i]);  // look时候颜色变化以及激活绿化属性
                }

                set_temp("module/"+modlevel+"_"+modname, mod_stats, owner);  // 玩家身上标记套装属性
                set_temp("fullsuit/"+modlevel+"_"+modname, mod_stats->bas_prop, owner);
        }
        else if( n == num )
        {
                if( !classp(tmp_stats = copy(query_temp("module/"+modlevel+"_"+modname, owner))) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                // 套装全齐了
                mod_stats->mod_name = modname;
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        data[file] = name;
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("mod_active", 1, ob);

                set_temp("module/"+modlevel+"_"+modname, mod_stats, owner);  // 玩家身上标记套装属性


                applied_prop = copy(mod_stats->bas_prop);
                stats = copy(mod_stats->adv_prop);
                apply = keys(stats);
                for( i = 0; i<sizeof(apply); i++ )
                {
                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }

                set_temp("fullsuit/"+modlevel+"_"+modname, applied_prop, owner);

                if( ob->is_item_make() ) // 备齐了全套装备
                        set_temp("modequip_itemmake_level", to_int(modlevel), owner);     // 玩家身上标记全套的自造套装等级
        }
        else
        {
                // 已经激活套装属性，附加新的套装单件属性
                // 首先检查已经激活的套装属性是否出了问题
                if( !classp(tmp_stats = copy(query_temp("module/"+modlevel+"_"+modname, owner))) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                mod_stats->mod_name = modname;

                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        data[file] = name;
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("mod_active", 1, ob);

                set_temp("module/"+modlevel+"_"+modname, mod_stats, owner);  // 玩家身上标记套装属性
                set_temp("fullsuit/"+modlevel+"_"+modname, mod_stats->bas_prop, owner);
        }

        // 战场上无效
        if( query_temp("warquest", owner) ) return;

        owner->reset_buff_cache();

        max_qi = query("max_qi", owner);
        max_jing = query("max_jing", owner);
        CHAR_D->setup_char(owner);
        if( query("eff_qi", owner) >= max_qi )
                max_qi = query("max_qi", owner) - max_qi;
        else
                max_qi = 0;
        if( query("eff_jing", owner) >= max_jing )
                max_jing = query("max_jing", owner) - max_jing;
        else
                max_jing = 0;
        addn("eff_qi", max_qi, owner);
        addn("eff_jing", max_jing, owner);

        return;
}

// 卸下套装部件
// ob套装部件 owner装备者
void unequip_module(object ob, object owner)
{
        class eqmodule mod_stats;
        class eqmodule tmp_stats;
        mapping data, stats, prop, applied_prop;
        mapping modparts;
        string *apply;
        string modname;
        string modlevel, file, name;
        object *inv, *obs;
        int i, j, n, flag = 0;
        int bas, num;

        if( ob->is_item_make() ) {
                if( ob->item_owner() != query("id", owner) )
                        return;
        }

        modlevel = query("mod_level", ob);
        modname = query("mod_name", ob);

        inv = owner->query_equipment_objects();
        if( ob->is_item_make() )        // 检查套装部件
        {
                obs = filter_array(inv,
                        (: query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) &&
                           $1->is_item_make() && $1->item_owner() == $(query("id", owner)) :));
        }
        else
                obs = filter_array(inv,
                        (: query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) && !$1->is_item_make() :));

        n = sizeof(obs);

        // 检查套装部件ob是否是套装里的一件
        file = query("mod_mark", ob);
        name = query("name", ob);

        // 标记套装文件
        modparts=query_temp("module/modparts_"+modlevel+"_"+modname, owner);
        if( !mapp(modparts) || !sizeof(modparts) )
                modparts = ([]);

        map_delete(modparts, file);
        set_temp("module/modparts_"+modlevel+"_"+modname, modparts, owner);


        // 标记套装件数
        addn_temp("module/modamount_"+modlevel+"_"+modname, -1, owner);
        if( query_temp("module/modamount_"+modlevel+"_"+modname, owner)<=0 )
                delete_temp("module/modamount_"+modlevel+"_"+modname, owner);

        // 删除装备套装部件标记
        delete_temp("mod_equip", ob);
        delete_temp("mod_active", ob); // look时候显示mod_prop颜色变化

        /*
        if( query_temp("module/modamount_"+modlevel+"_"+modname, owner) != n )
                error("套装装备件数出现混乱，请立刻提交bug给admin。\n");
        */

        // 少于2件不成套装
        if( n < 1 ) return;


        // 读取套装资料
        if( undefinedp(all[modlevel]) )
                mod_stats = load_module(modlevel);
        else
                mod_stats = copy(all[modlevel]);

        // 检查合法性
        //if( !valid_module(mod_stats) )
        //        return;

        bas = mod_stats->bas;
        num = mod_stats->num;

        // 如果onwer身上装备的套装件数+1未达到套装激活件数时，
        // 因为没附加过套装属性，所以不需要执行删除onwer套装属性
        if( n < bas-1 ) return;
        else if( n == bas-1 ) {
                if( !classp(tmp_stats = copy(query_temp("module/"+modlevel+"_"+modname, owner))) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                // 正好bas件，卸下套装部件，则消除套装的所有补充属性和基本属性
                for( i=0; i<sizeof(obs); i++ )
                {
                        if( obs[i] == ob ) continue;
                        delete_temp("mod_equip", obs[i]);   // 取消装备标记
                        delete_temp("mod_active", obs[i]);  // 取消激活标记
                }

                delete_temp("module/"+modlevel+"_"+modname, owner);
                delete_temp("fullsuit/"+modlevel+"_"+modname, owner);

                return;
        }
        else if( n == num-1 ) {
                if( !classp(tmp_stats = copy(query_temp("module/"+modlevel+"_"+modname, owner))) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                mod_stats->mod_name = modname;
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        map_delete(data, file);
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("module/"+modlevel+"_"+modname, mod_stats, owner);
                set_temp("fullsuit/"+modlevel+"_"+modname, mod_stats->bas_prop, owner);

                if( ob->is_item_make() )
                        delete_temp("modequip_itemmake_level", owner); // 删除套装等级，suit special调用

                return;
        }
        else
        {
                if( !classp(tmp_stats = copy(query_temp("module/"+modlevel+"_"+modname, owner))) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                mod_stats->mod_name = modname;  // 自造套装名称不是一样
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        map_delete(data, file);
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("module/"+modlevel+"_"+modname, mod_stats, owner);
                set_temp("fullsuit/"+modlevel+"_"+modname, mod_stats->bas_prop, owner);

                return;
        }
}

// 调用来自 /cmds/std/suit.c 使用套装特技
public int suit_special(object me, string arg)
{
        mapping buff, data;
        string msg;
        mapping map_status;
        string *mname;
        object *obs;
        int i, suitlvl, skill, temp;

        suitlvl = query_temp("modequip_itemmake_level", me);

        /*
        并额外附加套装特技 星辰之力(stars)。施展(special stars <项目>)
        后可提升下列某项状态 50% ，并持续 10 分钟。
        无视攻击、无视躲闪、无视招架、无视内功、抗毒效果、毒素伤害
        虚弱对手、解封绝招、绝招伤害、绝招命中、双倍伤害、
        化解伤害、抵抗虚弱、封存绝招、绝招防御、研究效果、汲取效果
        */

        obs = me->query_equipment_objects();
        obs = filter_array(obs,
                        (: $1->is_item_make() /*&& $1->item_owner() == $(query("id", me))*/ :));

        if( sizeof(obs) < 9 )
                return notify_fail("你没有装备全套的九件装备。\n");

        if( suitlvl < 4 )
                return notify_fail("你目前装备的套装等级不够，无法使用套装特技！\n");

        for( i=0; i<sizeof(obs); i++ )
        {
                if( query("qianghua/level", obs[i]) < 9 )
                        return notify_fail("由于"+obs[i]->name(1)+NOR"不是九星装备，无法使用套装特技！\n");
        }

        if( arg == "sun" ) // 增加命中
        {

                if( BUFF_D->check_buff(me, "powerofsun") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                if( query("neili", me) < 1000000 )
                        return notify_fail("你的内力不足，无法施展套装绝技。\n");

                if( query("neili", me) < query("max_neili", me) )
                        return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");

                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;
                set("neili", 0, me);

                msg = HIC "$N" HIC "一声长吟，只见太阳之力源源不尽被吸进全身装备，刹那间流光异彩，将其笼罩！\n" NOR;

                data = ([]);
                map_status = me->query_skill_map();
                if( sizeof(map_status) )
                {
                        mname  = keys(map_status);
                        temp = sizeof(map_status);

                        for( i=0; i<temp; i++ )
                                data[mname[i]] = skill;
                }

                data +=
                ([
                        "str"   : skill,
                        "int"   : skill,
                        "attack": skill,
                        "ap_power": 200,
                ]);

                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "atkup",
                        "type2" : "powerofsun",
                        "attr"  : "bless",
                        "name"  : "套装特技·太阳之力",
                        "time"  : skill,
                        "buff_data": data,
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·太阳之力运行完毕，将内力收回丹田。\n",
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }

        else if( arg == "moon" )  // 增加伤害
        {
                if( BUFF_D->check_buff(me, "powerofmoon") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                if( query("neili", me) < 1000000 )
                        return notify_fail("你的内力不足，无法施展套装绝技。\n");

                if( query("neili", me) < query("max_neili", me) )
                        return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");

                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;
                set("neili", 0, me);

                msg = HIR "$N举头望天，悠然一声长叹，刹那间月亮之力源源不尽被吸进全身装备，全身被红色的光芒包裹，杀气骤现！\n" NOR;

                data = ([]);
                map_status = me->query_skill_map();
                if( sizeof(map_status) )
                {
                        mname  = keys(map_status);
                        temp = sizeof(map_status);

                        for( i=0; i<temp; i++ )
                                data[mname[i]] = skill;
                }

                data +=
                ([
                        "str"   : skill,
                        "damage"   : skill,
                        "unarmed_damage": skill,
                        "da_power": 300,
                ]);

                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "damageup",
                        "type2" : "powerofmoon",
                        "attr"  : "bless",
                        "name"  : "套装特技·月亮之力",
                        "time"  : skill,
                        "buff_data": data,
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·月亮之力运行完毕，将内力收回丹田。\n",
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }

        else if( arg == "star" )
        {
                if( BUFF_D->check_buff(me, "powerofstar") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                if( query("neili", me) < 1000000 )
                        return notify_fail("你的内力不足，无法施展套装绝技。\n");

                if( query("neili", me) < query("max_neili", me) )
                        return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");

                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;
                set("neili", 0, me);

                msg = HIR "$N长啸一声，顿时星辰之力源源不尽被吸进全身装备，所过之处泛出红色血芒，令人心胆具寒。\n" NOR;

                data =
                ([
                        "leech_neili" : 30,
                        "leech_qi"    : 30,
                        "qi_abs_neili": 30,
                        "fatal_blow"  : 30,
                        "avoid_busy"  : 30,
                ]);

                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerup",
                        "type2" : "powerofstar",
                        "attr"  : "bless",
                        "name"  : "套装特技·星辰之力",
                        "time"  : skill,
                        "buff_data": data,
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·星辰之力运行完毕，将内力收回丹田。\n",
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }

        else
                write("套装特技使用格式：suit sun|moon|star\n");

        return 1;
}
