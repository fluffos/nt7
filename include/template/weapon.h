// weapon.h
// 模板包含之武器

string long()
{
        string  long;
        string *fix_list;
        string  fix_name;
        string  extra;

        long = query("long");

        // 显示前缀描述
        if (arrayp(fix_list = query("prefix")) && sizeof(fix_list))
        {
                foreach (fix_name in fix_list)
                        long += ITEM_D->get_prefix_desc(fix_name) + "\n";
        }
        // 显示后缀描述
        if (arrayp(fix_list = query("postfix")) && sizeof(fix_list))
        {
                foreach (fix_name in fix_list)
                        long += ITEM_D->get_postfix_desc(fix_name) + "\n";
        }

        if (stringp(extra = this_object()->extra_long()))
                long += extra;

        return long;
}

void init_damage(int damage) { set("weapon_prop/damage", damage); }

