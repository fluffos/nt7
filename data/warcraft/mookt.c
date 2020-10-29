// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "女性");                
        set("long", "威武的兽中之王[2;37;0m
它是清月风的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mookt");
        set("owner_name", "清月风");
        set_temp("owner", "mookt");
        set_temp("owner_name", "清月风");
        ::setup();
}
