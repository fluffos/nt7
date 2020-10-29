// enchase.c
#include <ansi.h>
inherit ITEM;

int is_equip_soul() { return 1; }

string chinese_s(int arg)
{
      if( arg == 1 ) return HIK "劣质的"; 
      if( arg == 2 ) return HIB "普通的"; 
      if( arg == 3 ) return HIR "精致的"; 
      if( arg == 4 ) return HIM "卓越的"; 
      if( arg == 5 ) return HIY "无暇的"; 
      if( arg == 6 ) return HIY "完美的";
      if( arg == 7 ) return HIY "神之的"; 
}

string extra_long()
{
        int i, level;
        string *apply, str, msg, type;
        mapping data;
        int value;

        str =  sprintf( WHT "\n魂魄属性 : 装备之魂<%s" NOR+WHT">，重量%d克，下线%s丢失\n" NOR,
                        this_object()->name(), this_object()->query_weight(),
                        (this_object()->query_autoload() || query("auto_load")) ? "不" : "" );

        if( query("status") ) str += sprintf(WHT "魂魄品质 : " NOR "%s\n" NOR, chinese_s(query("status")));

        return str;
}
