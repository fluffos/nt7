// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是汀汀婕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ting");
        set("owner_name", "汀汀婕");
        set_temp("owner", "ting");
        set_temp("owner_name", "汀汀婕");
        ::setup();
}
