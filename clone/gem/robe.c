#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_AUTOLOAD;

void create()
{
        set_name(HIC"魔法师袍"NOR, ({ "magic robe", "robe" }) );
        set("long", HIC"这是一件古怪的长袍，无论谁披上它都会有一种神奇的魔力附身。\n"NOR);
        set_weight(3000);
        set("unit", "件");
        set("value", 25000000);
        set("material", "cloth");
        set("armor_prop/armor", 600);
        set("armor_type", TYPE_CLOTH);
        set("no_put",1);
        set("no_pawn",1);
        set("no_beg",1);
        set("no_steal",1);
        set("no_clone",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();
}

int query_autoload() { return 1; }
