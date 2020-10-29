// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("幻舞朱雀王[2;37;0m[2;37;0m", ({"huashanmzride"}));        
        set("gender", "女性");                
        set("long", "幻舞朱雀王[2;37;0m
它是吴二丫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huashanmz");
        set("owner_name", "吴二丫");
        set_temp("owner", "huashanmz");
        set_temp("owner_name", "吴二丫");
        ::setup();
}
