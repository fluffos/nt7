// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m少[1;32m林[1;33m武[1;35m籍[2;37;0m[2;37;0m[2;37;0m", ({"wuji"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIG$少$HIG$林$HIY$武$HIM$籍$NOR$[2;37;0m
它是少林秘籍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miji");
        set("owner_name", "少林秘籍");
        set_temp("owner", "miji");
        set_temp("owner_name", "少林秘籍");
        ::setup();
}
