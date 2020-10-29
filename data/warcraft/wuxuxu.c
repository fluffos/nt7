// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m朱雀[2;37;0m[2;37;0m", ({"wux"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是武虚虚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wuxuxu");
        set("owner_name", "武虚虚");
        set_temp("owner", "wuxuxu");
        set_temp("owner_name", "武虚虚");
        ::setup();
}
