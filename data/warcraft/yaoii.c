// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("唉唉哎[2;37;0m[2;37;0m", ({"yaoiii"}));        
        set("gender", "男性");                
        set("long", "唉唉哎[2;37;0m
它是药唉唉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoii");
        set("owner_name", "药唉唉");
        set_temp("owner", "yaoii");
        set_temp("owner_name", "药唉唉");
        ::setup();
}
