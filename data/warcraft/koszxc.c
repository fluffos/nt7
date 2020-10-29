// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m库贱[2;37;0m[2;37;0m", ({"koszxcpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是贱库的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "koszxc");
        set("owner_name", "贱库");
        set_temp("owner", "koszxc");
        set_temp("owner_name", "贱库");
        ::setup();
}
