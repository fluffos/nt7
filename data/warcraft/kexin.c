// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m加菲[2;37;0m[2;37;0m", ({"jiafei"}));        
        set("gender", "男性");                
        set("long", "$HIY$加菲[2;37;0m
它是陌上陌黎的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kexin");
        set("owner_name", "陌上陌黎");
        set_temp("owner", "kexin");
        set_temp("owner_name", "陌上陌黎");
        ::setup();
}
