// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m迈巴赫[2;37;0m[2;37;0m", ({"mbh"}));        
        set("gender", "女性");                
        set("long", "finsih[2;37;0m
它是周肆丹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "btd");
        set("owner_name", "周肆丹");
        set_temp("owner", "btd");
        set_temp("owner_name", "周肆丹");
        ::setup();
}
