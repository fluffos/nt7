// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m山[5m[1;31m珍[2;37;0m[1;36m海[5m[1;35m味[2;37;0m[2;37;0m[2;37;0m", ({"dainty"}));        
        set("gender", "男性");                
        set("long", "$HIY$山$BLINK$$HIR$珍$NOR$$HIC$海$BLINK$$HIM$味$NOR$[2;37;0m
它是青菜萝卜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tasty");
        set("owner_name", "青菜萝卜");
        set_temp("owner", "tasty");
        set_temp("owner_name", "青菜萝卜");
        ::setup();
}
