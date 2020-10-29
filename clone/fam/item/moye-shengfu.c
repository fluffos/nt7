#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "莫邪圣符" NOR, ({ "moye fu", "moye", "fu" }) );
        set_weight(1);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "莫邪圣符可以将普通道具升级为自造道具，以后可以随时召唤升级后的道具。\n"
                                                "指令格式： upd <欲升级道具ID> to <升级后的道具ID> \n"
                                                                "目前仅仅限于升级防具类道具。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "张");
        }

        setup();
}

// 检查新ID是否合法
int check_legal_id(string id)
{
                int i;

                i = strlen(id);

                if ((strlen(id) < 4) || (strlen(id) > 10))
                {
                        write(WHT "\n对不起，升级后的ID必须是" HIY " 4 " NOR + WHT 
                                  "到" HIY " 10 " NOR + WHT "个英文字母。\n" NOR);
                        return 0;
                }

                while (i--)
        {
                        if (id[i] < 'a' || id[i] > 'z' )
                        {
                                write(WHT "\n对不起，你的英文名字只能用英文字母。\n" NOR);
                                return 0;
                        }
        }

                return 1;
}


void init()
{
        if (this_player() == environment())
        {
                add_action("do_upd", "upd");
        }
}


// 升级道具为自造兵器
// upd <目标道具ID> <升级后的ID>
int do_upd(string arg)
{
                object me;
                string tar_id, new_id, armor_type;
                object ob;
                mapping can_summon_list;
                string *key_can_summon_list;
                string head_file; // 自造物品文件开头
                string input_file; // 最后写入的文件信息
                mapping armor_prop, limit;
                string *key_armor_prop, *key_limit;
                int i;

                me = this_player();

                if (! arg)return notify_fail("指令格式: upd <欲升级道具ID> to <升级后的道具ID>\n");

                if (sscanf(arg, "%s to %s", tar_id, new_id) != 2)
                        return notify_fail("指令格式: upd <欲升级道具ID> to <升级后的道具ID>\n");
                
/*
1、首先判断该道具是否存在。
2、该道具是否为防具。
3、该道具是否可升级
3.1 该道具是否下线不丢失
3.2 该道具是否为自造道具。
3.3 该物品新ID是否合法，全为英文名。
3.4 该物品新ID是否与现有自造物品ID重复（can_summon)。
*/
        // 首先判断该道具是否存在
                if (! objectp(ob = present(tar_id, me)))
                        return notify_fail("你身上好象没有这个物品吧！\n");

                // 检查ob是否为防具
                if (! stringp(armor_type = ob->query("armor_type")))
                        return notify_fail("对不起，只能升级防具类物品。\n");

                // 该道具是否可升级
                // 该道具是否下线不丢失
                if (! ob->query_autoload())
                        return notify_fail("你只能升级下线不丢失的物品。\n");
                
                // 该道具是否为自造道具
                if (ob->is_item_make())
                        return notify_fail("自造物品不能升级。\n");                

                // 
                if (ob->query("no_upd"))
                        return notify_fail("该特殊物品不能升级。\n");
                        
                // 该物品新ID是否合法，全为英文名
                if (! check_legal_id(new_id))return 1;
                                                
                // 该物品新ID是否与现有自造物品ID重复（can_summon)
                can_summon_list = me->query("can_summon");

                if (mapp(can_summon_list))
                {
                        if (sizeof(can_summon_list))
                        {
                                key_can_summon_list = keys(can_summon_list);

                                if (member_array(new_id, key_can_summon_list) != -1)
                                {
                                        return notify_fail("升级后的ID名有重复，请输入 summon 查看已有的ID名。\n");
                                }
                        }
                }
                
                // 如果是勋章则加上诸神赐予 xxx(id)
                if (ob->query("armor_type") == "medal" ||
                    ob->query("armor_type") == "medal2")
                {
                        ob->set("long", ob->query("long") + 
                                        HIC "只见勋章的边缘刻着一排小字：诸神赐予 " + me->name() + HIC + "(" + me->query("id") + ")\n" NOR);
                }


/*
4、进行升级
4.1 根据道具类型设置相关数据，并写入文件。
4.2 设置该玩家can_summon 数据。
4.3 destruct 该道具和升级道具，并提示summon
*/

                // 4、进行升级
                // 4.1 根据道具类型设置相关数据，并写入文件。
                head_file = 
                "\n"
                "#include <ansi.h>\n"
                "#include <armor.h>\n"
                "\n"
                "inherit ==ARMOR_TYPE==;\n"
                "inherit F_ITEMMAKE;\n"
                "\n"
                "void create()\n"
                "{\n"
                "\tset_name(==ARMOR_NAME==, ({ ==ARMOR_ID== }));\n"
                "\tset_weight(==ARMOR_WEIGHT==);\n"
                "\tset(\"item_make\", 1);\n"
                "\tset(\"unit\", ==ARMOR_UNIT==);\n"
                "\tset(\"long\", ==ARMOR_LONG==);\n"
                "\tset(\"value\", ==ARMOR_VALUE==);\n"
                "\tset(\"point\", ==ARMOR_POINT==);\n"
                "\tset(\"material\", ==ARMOR_MATERIAL==);\n";
                if (ob->query("wear_msg"))
                {
                        head_file += "\tset(\"wear_msg\", \"" + ob->query("wear_msg") + "\");\n";
                }
                if (ob->query("remove_msg"))
                {
                        head_file += "\tset(\"remove_msg\", \"" + ob->query("remove_msg") + "\");\n";
                }
                head_file += "\tif (! check_clone()) return;\n";
                head_file += "\trestore();\n";

                // 替换head_file中内容
                // 1. ==ARMOR_TYPE== 防具类型
                //    ==ARMOR_ID==
                head_file = replace_string(head_file, "==ARMOR_TYPE==", upper_case(armor_type));
                head_file = replace_string(head_file, "==ARMOR_ID==", "\"" + new_id + "\"");
                // 2. ==ARMOR_NAME== 名称
                head_file = replace_string(head_file, "==ARMOR_NAME==", "\"" + ob->name() + "\"");
                // 3. ==ARMOR_WEIGHT==
                head_file = replace_string(head_file, "==ARMOR_WEIGHT==", sprintf("%d", ob->query_weight()));
                // 4. ==ARMOR_UNIT==
                head_file = replace_string(head_file, "==ARMOR_UNIT==", "\"" + ob->query("unit") + "\"");
                // 5. ==ARMOR_LONG==
                head_file = replace_string(head_file, "==ARMOR_LONG==", "\"" + (ob->query("long") ? ob->query("long") : ob->query("name")) + "\\n\"");
                // 6. ==ARMOR_VALUE==
                head_file = replace_string(head_file, "==ARMOR_VALUE==", sprintf("%d", ob->query("value")));
                // 7. ==ARMOR_POINT==
                head_file = replace_string(head_file, "==ARMOR_POINT==", sprintf("%d", ob->query("armor_prop/armor") * 5 / 6));
                // 8. ==ARMOR_MATERIAL==
                head_file = replace_string(head_file, "==ARMOR_MATERIAL==", ob->query("material") ? 
                                                                            "\"" + ob->query("material") + "\"" : 
                                                                                "\"" +  "steel" + "\"");
                        
                // 11.设置道具的armor_pro
                armor_prop = ob->query("armor_prop");
                
                key_armor_prop = keys(armor_prop);
                input_file = head_file;
                if (sizeof(key_armor_prop))
                {                
                        for (i = 0; i < sizeof(key_armor_prop); i ++ )
                        {
                                if (key_armor_prop[i] == "armor")continue;                                
                                
                                // 如果为护身符 则暂时不写入fy&qy值，在循环后单独写入
                                if (ob->query("armor_type") == "myheart" || 
                                    ob->query("armor_type") == "myheart2")
                                {
                                        if (key_armor_prop[i] =="fy" || key_armor_prop[i] == "qy")
                                                continue;
                                }

                                input_file += "\tset(\"armor_prop/" + key_armor_prop[i] + "\", ";
                                                                
                                if (stringp(armor_prop[key_armor_prop[i]]))
                                        input_file += armor_prop[key_armor_prop[i]] + ");\n";
                                else                                        
                                        input_file += sprintf("%d", armor_prop[key_armor_prop[i]]) + ");\n";
                        } 
                        
                        // 单独写入福缘及气运的计算公式
                        if (ob->query("armor_type") == "myheart" || 
                            ob->query("armor_type") == "myheart2")
                        {
                                input_file += "\tset(\"armor_prop/fy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/fy")) + " + f_enchase_points(0));\n";
                                input_file += "\tset(\"armor_prop/qy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/qy")) + " + f_enchase_points(1));\n";                                
                        }
                
                }
                input_file += "\tset(\"armor_prop/armor\", apply_armor());\n";
                // 如果无armor_prop不能装备，可设置
                input_file += "\tset(\"armor_prop/can_wear\", 1);\n";

                // 12. 设置道具limit信息
                limit = ob->query("limit");
                if (mapp(limit))key_limit = keys(limit);
                if (sizeof(key_limit))
                {
                        for (i = 0; i < sizeof(key_limit); i ++ )
                        {
                                input_file += "\tset(\"limit/" + key_limit[i] + "\", ";
                                input_file += sprintf("%d", limit[key_limit[i]]) + ");\n";
                        }                        
                }

                input_file += "\n\tsetup();\n";
                input_file += "}\n\n";
                input_file += "string long() { return query(\"long\") + item_long(); }\n\n";

                // 写入文件
                if (! ITEM_D->extern_write_file("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c",
                                              input_file, 
                                                                  1) )
                {
                        return notify_fail("升级失败，写入文件异常。\n");
                }                                

                // 更新道具
                load_object("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");

                // 记录
                log_file("moyefu", me->query("id") + " 于 " + ctime(time()) + " 使用莫邪符升级 " + new_id + "。\n");
                
                // 设置CAN_SUMMON
                me->set("can_summon/" + new_id, "/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");
                me->save();

                // 提示
                write(HIG "升级完毕，请输入指令 summon " + new_id + " 召回升级后的物品。\n" NOR);

                destruct(ob);
                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}