// enchase.c
#include <ansi.h>
inherit ITEM;

int is_tessera() { return 1; }

string chinese_s(mixed arg)
{
      if( !stringp(arg) )  return HIW "无";
      if( arg == "metal" ) return HIY "金";
      if( arg == "wood" )  return HIM "木";
      if( arg == "water" ) return HIB "水";
      if( arg == "fire" )  return HIR "火";
      if( arg == "earth" ) return HIG "土";
      if( arg == "magic" ) return HIG "魔";
}

mapping dict = ([
        "axe"           :"斧",
        "bow"           :"弓",
        "sword"         :"剑",
        "blade"         :"刀",
        "club"          :"棍",
        "dagger"        :"匕首",
        "fork"          :"叉",
        "hammer"        :"锤",
        "staff"         :"杖",
        "throwing"      :"暗器",
        "whip"          :"鞭",
        "xsword"        :"箫",
        "head"          :"头盔",
        "neck"          :"项链",
        "cloth"         :"衣服",
        "charm"         :"符文",
        "rings"         :"戒指",
        "armor"         :"护甲",
        "surcoat"       :"披风",
        "waist"         :"腰带",
        "wrists"        :"护腕",
        "shield"        :"盾甲",
        "hands"         :"铁掌",
        "boots"         :"靴子",
        "finger"        :"指套",
        "all"           :"所有类型",
]);

string to_chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}


string extra_long()
{
        int i/*, level*/;
        string *apply, str/*, msg*/, type;
        mapping data;
        int value;

        str =  sprintf( WHT "\n物品属性 : 镶嵌物<%s" NOR+WHT">，重量%d克，下线%s丢失\n" NOR,
                        this_object()->name(), this_object()->query_weight(),
                        (this_object()->query_autoload() || query("auto_load")) ? "不" : "" );

        if( mapp(query("magic")) )
        {
                str += sprintf(WHT "魔力属性 : %s\n" NOR, chinese_s(query("magic/type")));
                str += sprintf(WHT "魔 力 值 : %d\n" NOR, (int)query("magic/power"));
        }

        type = query("enchase/type");
        if( type )
                str += sprintf(WHT "可镶装备 : %s(%s)\n" NOR, to_chinese(type), type);
/*
        level = query("enchase/level");
        if( level )
                str += sprintf(WHT "可镶等级 : %d\n" NOR, level);
*/

        if( mapp(data = copy(query("enchase/weapon_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBCYN "镶嵌兵器" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/armor_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBYEL "镶嵌防具" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/rings_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBGRN "镶嵌饰品" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/apply_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBCYN "拥有属性" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }

        return str;
}