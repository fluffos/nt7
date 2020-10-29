// apprentice.c
// Written by Lonely@nitan.org

int is_apprentice_of(object ob)
{
        mapping family;
//      string *fams;

        if( !mapp(family = query("family")) ) return 0;

        if( family["master_id"] == (string)query("id", ob) &&
            family["master_name"] == (string)query("name", ob) )
                return 1;

/*
        if( !arrayp(fams = query("reborn/fams")) || 
            !query("family/family_name", ob) )
                return 0;

        if( member_array(query("family/family_name", ob), fams) != -1 ) 
                return 1;
*/

        return 0;
}

void assign_apprentice(string title, int privs)
{
        mapping family;

        if( !mapp(family = query("family")) ) return;
        family["title"] = title;
        family["privs"] = privs;
        if( userp(this_object()) || !query("title") ) {
                switch( family["generation"] ) {
                case 0:
                        set("title", family["family_name"] + family["title"]);
                        break;
                case 1:
                        set("title", family["family_name"] + "开山祖师");
                        break;
                default:
                        set("title", sprintf("%s第%s代%s", family["family_name"],
                                chinese_number(family["generation"]), family["title"]));
                        break;
                }
        }
}

// This is used for NPC, or start a new family for a player.
void create_family(string family_name, int generation, string title)
{
        mapping family;
        family = allocate_mapping(6);
        family["family_name"] = family_name;
        family["generation"] = generation;
        set("family", family);
        // priv = -1 for ALL privileges.
        assign_apprentice( title, -1 );
}

int recruit_apprentice(object ob)
{
        mapping my_family, family;
        string class1, class2;
        string family_name;

        if( ob->is_apprentice_of(this_object()) )
                return 0;

        if( !mapp(my_family = query("family")) )
                return 0;

        // 这里处理判师的bug
        family_name = query("family/family_name", ob);
        if( family_name && family_name != my_family["family_name"] )
        {
                if( !query("betrayer/" + family_name, ob) )
                {
                        set("weiwang", 0, ob); 
                        addn("betrayer/times", 1, ob); 
                        addn("betrayer/" + family_name, 1, ob);
                        delete("quest", ob); 
                        delete_temp("quest", ob); 
                }
        }

        class1 = query("class");
        class2 = query("class", ob);
        if( stringp(class1) &&
            class2 != "bonze" && class2 != "eunach" &&
            class1 != "bonze" && class1 != "eunach" )
                set("class", class1, ob);

        family = allocate_mapping(sizeof(my_family));
        family["master_id"]   = query("id");
        family["master_name"] = query("name");
        family["family_name"] = my_family["family_name"];
        family["generation"]  = my_family["generation"] + 1;
        family["enter_time"]  = time();

        /*
        if( family["family_name"] == "欧阳世家" ) {
                if( query("can_not_change", ob) && !query("old_surname", ob) )
                        set("old_surname", query("surname", ob), ob);
                set("surname", "欧阳", ob);
                set("born_family", "欧阳世家", ob);
                ob->set_name();
        }

        if( family["family_name"] == "关外胡家" ) {
                 if( query("can_not_change", ob) && !query("old_surname", ob) )
                        set("old_surname", query("surname", ob), ob);
                set("surname", "胡", ob);
                set("born_family", "关外胡家", ob);
                ob->set_name();
        }

        if( family["family_name"] == "慕容世家" ) {
                 if( query("can_not_change", ob) && !query("old_surname", ob) )
                        set("old_surname", query("surname", ob), ob);
                set("surname", "慕容", ob);
                set("born_family", "慕容世家", ob);
                ob->set_name();
        }

        if( family["family_name"] == "段氏皇族" ) {
                 if( query("can_not_change", ob) && !query("old_surname", ob) )
                        set("old_surname", query("surname", ob), ob);
                set("surname", "段", ob);
                set("born_family", "段氏皇族", ob);
                ob->set_name();
        }
        */

        // 拜师后不再可以通过北京文庙修改性格
        if( !query("can_not_change", ob) && family["family_name"] != "古村" )
                set("can_not_change", 1, ob);

        if( stringp(family_name) && family_name == family["family_name"] )
                family["gongji"] = query("family/gongji", ob);

        if( query("family/first", ob) && family_name == family["family_name"] )
                family["first"] = 1;

        if( query("inherit_title") ) {
                set("title", query("inherit_title", this_object()), ob);
                set("family", family, ob);
                return 1;
        } else
        if( query("born_family") != "没有" )
                family["title"] = "传人";
        else
                family["title"] = "弟子";

        set("family", family, ob);
        ob->assign_apprentice(family["title"], 0);
        return 1;
}

string query_bunch()
{
        return query("bunch/bunch_name");
}

string query_family()
{
        return query("family/family_name");
}

string query_master()
{
        return query("family/master_name");
}

string query_generation()
{
        return query("family/generation");
}