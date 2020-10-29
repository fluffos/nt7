#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "大燕玉玺" NOR, ({ "dayan yuxi", "yuxi" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "stone");
            set("long", "一个玉玺，上面刻着大燕国号，看起来有些年代了。\n");
          }
    set("owner", "慕容博");
    setup();
}
