// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m啸月[1;34m苍狼[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这头妖狼体态健硕、面目狰狞，眼睛幽幽泛着蓝光，令人毛骨悚然。[2;37;0m
它是雅各布的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wolf");
        set("owner_name", "雅各布");
        set_temp("owner", "wolf");
        set_temp("owner_name", "雅各布");
        ::setup();
}
