#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"大燕族谱"NOR, ({ "dayan zupu", "zu pu" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本很老旧的书，上面写着“大燕族谱”。\n");
          }
    set("owner", "慕容复");
    setup();
}
