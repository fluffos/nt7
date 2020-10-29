// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// identifyd.c

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

mapping gems = ([
        "ruby":         "红宝石",
        "topaz":        "黄宝石",
        "sapphire":     "蓝宝石",
        "emerald":      "翡翠绿",
        "amethyst":     "紫水晶",
        "diamond":      "水晶钻",
        "skull":        "骷髅头",
]);
mapping gems_color = ([
        "ruby":         HIR,
        "topaz":        HIY,
        "sapphire":     HIB,
        "emerald":      HIG,
        "amethyst":     MAG,
        "diamond":      HIW,
        "skull":        WHT,
]);

string *gems_level = ({
        "细碎的",
        "",
        "稀世",
        "神之",
});

string *gems_level_id = ({
        "chipped",
        "",
        "flawless",
        "magic",
});

string query_gem_name(string socket, int level)
{
        return sprintf("%s%s%s"NOR, gems_color[socket], gems_level[level - 1], gems[socket]);
}

string query_gem_id(string socket, int level)
{
        if( gems_level_id[level - 1] == "" ) return socket;
        return sprintf("%s %s", gems_level_id[level - 1], socket);
}

mixed identify_ob(object me, object ob)
{
        int     idx, i, level, mf;
        string  filename, name, id, *my_id;
        string  gem, s;
        mixed   obj;
        mapping data, temp;

        level = query("level", ob); // 只有宝石种类，没有等级
        if( !level )
        {
                mf = query_temp("magic_find", me);
                i = random(100);
                i += mf;
                if (i < 50) { level = 1; s = "c"; }
                else if (i < 75) { level = 2; s = ""; }
                else if (i < 95) { level = 3; s = "f"; }
                else { level = 4; s = "m"; }
                gem = query("id", ob);
                filename = s+gem;
                id = query_gem_id(gem, level);
                name = query_gem_name(gem, level);
                my_id = ({ id });
        } else
        {
                id = query("id", ob);
                name = query("name", ob);
                my_id = ob->my_id();
                filename = query("material", ob);
                if( !filename )
                {
                        filename = base_name(ob);
                        idx = strsrch(filename, "/", -1);
                        filename = filename[idx+1..];
                }
        }

        temp = ([]);
        data = ([]);
        temp["weapon_prop"] = EQUIPMENT_D->apply_gem_prop("weapon", level, level-1);
        temp["armor_prop"] = EQUIPMENT_D->apply_gem_prop("armor", level, level-1);
        //temp["rings_prop"] = EQUIPMENT_D->apply_gem_prop("rings", level, level-1);
        temp["SN"] = 1 + random(9);
        temp["type"] = "all";
        data["enchase"] = temp;
        data["name"] = name;

        obj = TEMPLATE_D->create_object("/inherit/template/gem/" + filename, id, data, 1);
        obj->set_name(name, my_id);

        return obj;
}

// 无上神品->上古神品->中古神品->远古神品->太古神品
// 太始、太初、太玄 太虚、洪荒
// 冥古宙、太古宙、元古宙和显生宙
// 其中元古宙又划分为古元古代、中元古代和新元古代；
// 显生宙划分古生代、中生代和新生代。
varargs int identify_ultimate_ob(object item, int close)
{
        mapping data, prop;
        string *apply;
        mixed inset;
        int i, n, sn;
        int r_effect, d_effect, p_effect;

        r_effect = 0;
        d_effect = 0;
        p_effect = 0;

        sn=query("enchase/SN", item);
        if( sn == 37 && !query("ultimate/37", item) )
        {
                addn("enchase/apply_prop/research_effect", 10, item);
                if( query("enchase/apply_prop/research_effect", item)>40 )
                        set("enchase/apply_prop/research_effect", 40, item);
                addn("enchase/apply_prop/practice_effect", 10, item);
                if( query("enchase/apply_prop/practice_effect", item)>40 )
                        set("enchase/apply_prop/practice_effect", 40, item);
                addn("enchase/apply_prop/derive_effect", 10, item);
                if( query("enchase/apply_prop/derive_effect", item)>40 )
                        set("enchase/apply_prop/derive_effect", 40, item);
                addn("enchase/flute", 1, item);
                addn("enchase/SN", -(random(9)+1), item);
                set("ultimate/37", 1, item);
                item->save();
                return 1;
        } else
        if( sn == 39 && !query("ultimate/39", item) )
        {
                addn("enchase/apply_prop/research_effect", 15, item);
                if( query("enchase/apply_prop/research_effect", item)>40 )
                        set("enchase/apply_prop/research_effect", 40, item);
                addn("enchase/apply_prop/practice_effect", 15, item);
                if( query("enchase/apply_prop/practice_effect", item)>40 )
                        set("enchase/apply_prop/practice_effect", 40, item);
                addn("enchase/apply_prop/derive_effect", 15, item);
                if( query("enchase/apply_prop/derive_effect", item)>40 )
                        set("enchase/apply_prop/derive_effect", 40, item);
                addn("enchase/flute", 1, item);
                set("ultimate/39", 1, item);
                item->save();
                return 1;
        } else
        if( sn == 69 && !query("ultimate/69", item )
         && query("armor_type", item) && query("armor_type", item) != "hands"
         && query("armor_type", item) != "finger" )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] = data[apply[i]] * 3 / 2;

                prop = copy(query("armor_prop", item));
                map_delete(prop, "armor");

                if( sizeof(prop) > 0 )
                {
                        apply = keys(prop);
                        for( i=0;i<sizeof(apply);i++ )
                        {
                                prop[apply[i]] = prop[apply[i]] * 3 / 2;
                                if( query("quality_level", item) == 4 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                } else
                                if( query("quality_level", item) == 5 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 3;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                } else
                                if( query("quality_level", item) == 6 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 8;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 4;
                                        else if( sizeof(apply) == 3 )
                                                prop[apply[i]] = prop[apply[i]] * 3;
                                        else
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                }
                        }
                }
                set("rare/apply_prop", prop, item);

                inset=query("insert", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["apply_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = r_effect * 3 / 2;
                data["derive_effect"] = d_effect * 3 / 2;
                data["practice_effect"] = p_effect * 3 / 2;

                data["reduce_busy"]     = EQUIPMENT_D->query_prop_value("reduce_busy", 1 + random(2));
                data["avoid_busy"]      = EQUIPMENT_D->query_prop_value("avoid_busy", 1 + random(4));
                data["counter_damage"]  = EQUIPMENT_D->query_prop_value("counter_damage", 1 + random(6));
                data["avoid_weak"]      = EQUIPMENT_D->query_prop_value("avoid_weak", 1 + random(4));
                data["avoid_freeze"]    = EQUIPMENT_D->query_prop_value("avoid_freeze", 1 + random(4));
                data["add_forget"]      = EQUIPMENT_D->query_prop_value("add_forget", 1 + random(4));
                data["reduce_damage"]   = EQUIPMENT_D->query_prop_value("reduce_damage", 1 + random(3));

                set("enchase/apply_prop", data, item);
                set("ultimate/69", 1, item);
                set("ultimate/ob", 1, item);
                item->save();

                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说上古神品" + item->name() + HIM +
                              "来到了人间。");

                //MYGIFT_D->check_mygift(find_player(item_owner()), "newbie_mygift/ultimate");

                log_file("static/ultimate", sprintf("%s Have 69 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 87 && !query("ultimate/87", item) )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                if (item->is_weapon() || item->is_unarmed_weapon())
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] = data[apply[i]] * 3 / 2;

                        if( item->is_weapon() )
                        {
                                prop = copy(query("weapon_prop", item));
                                map_delete(prop, "damage");
                        } else
                        {
                                prop = copy(query("armor_prop", item));
                                map_delete(prop, "armor");
                                map_delete(prop, "unarmed_damage");
                        }

                        if( sizeof(prop) > 0 )
                        {
                                apply = keys(prop);
                                for( i=0;i<sizeof(apply);i++ )
                                {
                                        prop[apply[i]] = prop[apply[i]] * 3 / 2;
                                        if( query("quality_level", item) == 4 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        } else
                                        if( query("quality_level", item) == 5 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 3;
                                                else if( sizeof(apply) == 2 )
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        } else
                                        if( query("quality_level", item) == 6 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 8;
                                                else if( sizeof(apply) == 2 )
                                                        prop[apply[i]] = prop[apply[i]] * 4;
                                                else if( sizeof(apply) == 3 )
                                                        prop[apply[i]] = prop[apply[i]] * 3;
                                                else
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        }
                                }
                        }
                        set("rare/apply_prop", prop, item);

                        inset=query("insert", item);
                        if (!inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["apply_prop"]) && sizeof(prop))
                                {
                                        if (!undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (!undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (!undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }
                        if( r_effect ) r_effect = 30 + r_effect * 3 / 2;
                        if( d_effect ) d_effect = 30 + d_effect * 3 / 2;
                        if( p_effect ) p_effect = 30 + p_effect * 3 / 2;
                        data["research_effect"] = r_effect;
                        data["derive_effect"] = d_effect;
                        data["practice_effect"] = p_effect;

                        data["add_busy"]        = EQUIPMENT_D->query_prop_value("add_busy", 1 + random(5));
                        data["add_weak"]        = EQUIPMENT_D->query_prop_value("add_weak", 1 + random(3));
                        data["add_freeze"]      = EQUIPMENT_D->query_prop_value("add_freeze", 1 + random(3));
                        data["avoid_forget"]    = EQUIPMENT_D->query_prop_value("avoid_forget", 1 + random(3));
                        data["add_damage"]      = EQUIPMENT_D->query_prop_value("add_damage", 1 + random(3));
                        data["add_skill"]       = EQUIPMENT_D->query_prop_value("add_skill", 1 + random(4));

                        set("enchase/apply_prop", data, item);
                        set("ultimate/87", 1, item);

                        if (!close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说上古神品" + item->name() + HIM +
                                "来到了人间。");

                } else
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] *= 2;

                        prop = copy(query("armor_prop", item));
                        map_delete(prop, "armor");

                        if( sizeof(prop) > 0 )
                        {
                                apply = keys(prop);
                                for( i=0;i<sizeof(apply);i++ )
                                {
                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        if( query("quality_level", item) == 4 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        } else
                                        if( query("quality_level", item) == 5 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 3;
                                                else if( sizeof(apply) == 2 )
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        } else
                                        if( query("quality_level", item) == 6 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        prop[apply[i]] = prop[apply[i]] * 8;
                                                else if( sizeof(apply) == 2 )
                                                        prop[apply[i]] = prop[apply[i]] * 4;
                                                else if( sizeof(apply) == 3 )
                                                        prop[apply[i]] = prop[apply[i]] * 3;
                                                else
                                                        prop[apply[i]] = prop[apply[i]] * 2;
                                        }
                                }
                        }
                        set("rare/apply_prop", prop, item);

                        inset=query("insert", item);
                        if (!inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["apply_prop"]) && sizeof(prop))
                                {
                                        if (!undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (!undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (!undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }

                        if( r_effect ) r_effect = 40 + r_effect * 2;
                        if( d_effect ) d_effect = 40 + d_effect * 2;
                        if( p_effect ) p_effect = 40 + p_effect * 2;
                        data["research_effect"] = r_effect;
                        data["derive_effect"] = d_effect;
                        data["practice_effect"] = p_effect;

                        data["reduce_busy"]     = 5;
                        data["avoid_busy"]      = 5;
                        //data["avoid_fear"]      = 5;
                        data["counter_damage"]  = 5;
                        data["avoid_weak"]      = 5;
                        data["avoid_freeze"]    = 5;
                        data["add_forget"]      = 5;
                        data["reduce_damage"]   = 5;
                        set("enchase/apply_prop", data, item);
                        set("ultimate/87", 1, item);

                        if (!close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说远古神品" + item->name() + HIM +
                                "来到了人间。");
                }

                set("ultimate/ob", 1, item);
                item->save();
                log_file("static/ultimate", sprintf("%s Have 87 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 105 && !query("ultimate/105", item) )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 2;

                if( item->is_weapon() )
                {
                        prop = copy(query("weapon_prop", item));
                        map_delete(prop, "damage");
                }
                else
                {
                        prop = copy(query("armor_prop", item));
                        map_delete(prop, "unarmed_damage");
                        map_delete(prop, "armor");
                }

                if( sizeof(prop) > 0 )
                {
                        apply = keys(prop);
                        for( i=0;i<sizeof(apply);i++ )
                        {
                                prop[apply[i]] = prop[apply[i]] * 2;
                                if( query("quality_level", item) == 4 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                } else
                                if( query("quality_level", item) == 5 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 3;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                } else
                                if( query("quality_level", item) == 6 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 8;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 4;
                                        else if( sizeof(apply) == 3 )
                                                prop[apply[i]] = prop[apply[i]] * 3;
                                        else
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                }
                        }
                }
                set("rare/apply_prop", prop, item);

                inset=query("insert", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["apply_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }

                if( r_effect ) r_effect = 100 + r_effect * 2;
                if( d_effect ) d_effect = 100 + d_effect * 2;
                if( p_effect ) p_effect = 100 + p_effect * 2;
                data["research_effect"] = r_effect;
                data["derive_effect"] = d_effect;
                data["practice_effect"] = p_effect;

                data["add_busy"]        = 15;
                data["add_weak"]    = 15;
                data["add_freeze"]   = 15;
                data["avoid_forget"] = 15;
                data["add_damage"]      = 60;
                data["add_skill"]  = 300;

                set("enchase/apply_prop", data, item);
                set("ultimate/105", 1, item);
                set("ultimate/ob", 1, item);
                item->save();
                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说远古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("%s Have 105 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 121 && !query("ultimate/121", item) && close )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 3;

                if( item->is_weapon() )
                {
                        prop = copy(query("weapon_prop", item));
                        map_delete(prop, "damage");
                }
                else
                {
                        prop = copy(query("armor_prop", item));
                        map_delete(prop, "unarmed_damage");
                        map_delete(prop, "armor");
                }

                if( sizeof(prop) > 0 )
                {
                        apply = keys(prop);
                        for( i=0;i<sizeof(apply);i++ )
                        {
                                prop[apply[i]] = prop[apply[i]] * 2;
                                if( query("quality_level", item) == 4 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 3;
                                } else
                                if( query("quality_level", item) == 5 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 4;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                } else
                                if( query("quality_level", item) == 6 )
                                {
                                        if( sizeof(apply) == 1 )
                                                prop[apply[i]] = prop[apply[i]] * 16;
                                        else if( sizeof(apply) == 2 )
                                                prop[apply[i]] = prop[apply[i]] * 8;
                                        else if( sizeof(apply) == 3 )
                                                prop[apply[i]] = prop[apply[i]] * 4;
                                        else
                                                prop[apply[i]] = prop[apply[i]] * 2;
                                }
                        }
                }
                set("rare/apply_prop", prop, item);

                inset=query("insert", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["apply_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = 2000 + r_effect * 3;
                data["derive_effect"] = 2000 + d_effect * 3;
                data["practice_effect"] = 2000 + p_effect * 3;

                data["qi_abs_neili"] = 96;
                data["through_armor"] = 96;
                data["qi_abs_neili"] = 96;
                data["leech_qi"] = 96;
                data["leech_neili"] = 96;
                data["double_damage"] = 200;
                data["add_blind"] = 96;
                data["avoid_blind"] = 96;
                data["add_busy"]        = 96;
                data["add_weak"]    = 96;
                data["avoid_forget"] = 96;
                data["add_damage"]      = 200;
                data["add_skill"]  = 1000;
                data["add_freeze"] = 96;
                data["avoid_freeze"] = 96;
                data["fatal_blow"] = 96;
                data["full_self"] = 96;
                data["avoid_die"] = 96;

                data["magic_find"] = 100;
                data["add_reward"] = 100;

                data["reduce_busy"]     = 96;
                data["avoid_busy"]      = 96;
                data["counter_damage"]       = 96;
                data["avoid_weak"]     = 96;
                data["add_forget"]= 96;
                data["reduce_damage"]   = 96;

                data["ap_power"]        = 120;
                data["dp_power"]        = 120;
                data["da_power"]        = 120;
                data["avoid_parry"]     = 96;
                data["avoid_dodge"]     = 96;
                data["avoid_force"]     = 96;
                data["avoid_attack"]    = 96;

                set("enchase/apply_prop", data, item);
                set("ultimate/121", 1, item);
                set("ultimate/ob", 1, item);
                item->save();
                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说太古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("%s Have 121 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
                return 0;
}
