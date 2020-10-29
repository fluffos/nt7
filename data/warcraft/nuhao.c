// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神风[1;31m[2;37;0m[2;37;0m", ({"shenfeng"}));        
        set("gender", "男性");                
        set("long", "神风[2;37;0m
它是神风怒嚎的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nuhao");
        set("owner_name", "神风怒嚎");
        set_temp("owner", "nuhao");
        set_temp("owner_name", "神风怒嚎");
        ::setup();
}
