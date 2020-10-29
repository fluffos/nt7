// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("歧天[2;37;0m[2;37;0m", ({"qitian"}));        
        set("gender", "女性");                
        set("long", "幻入南柯千世劫，道披天下一衣霜。[2;37;0m
它是净无幻的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jingwuhuan");
        set("owner_name", "净无幻");
        set_temp("owner", "jingwuhuan");
        set_temp("owner_name", "净无幻");
        ::setup();
}
