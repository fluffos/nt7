// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m避水金睛兽[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "它有一双金色的瞳眸，眸中波光呈琉璃之色，看去似还有佛光涌现[2;37;0m
它是慕容云染的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mryr");
        set("owner_name", "慕容云染");
        set_temp("owner", "mryr");
        set_temp("owner_name", "慕容云染");
        ::setup();
}
