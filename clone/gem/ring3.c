#include <ansi.h>
#include <armor.h>

inherit S_RING;
inherit F_AUTOLOAD;

void create()
{
        set_name(HIY"瑶池神戒"NOR, ({ "magic ring", "ring" }));
        set("long", HIC"这是一个从远古流传下来的戒指，上面刻着一些奇怪的咒语。\n"NOR);
        set("weight", 400);
        set("unit", "个");
        set("value", 5000000);
        set("material", "gem");
        set("armor_prop/armor", 30);
        set("armor_type", TYPE_FINGER);
        set("no_put",1);
        set("no_beg",1);
        set("no_steal",1);
        set("no_clone",1);
        set("no_pawn",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();
}        

int query_autoload() { return 1; }
