
mapping soul_list = ([
        "weapon"        :"武器",
        "head"          :"头盔",
        "neck"          :"项链",
        "cloth"         :"战衣",
        "armor"         :"护甲",
        "surcoat"       :"披风",
        "waist"         :"腰带",
        "wrists"        :"护腕",
        "hands"         :"铁掌",
        "boots"         :"战靴",
        "finger"        :"指套",
        "rings"         :"戒指",
        "charm"         :"护身符",
]);
        
void create_soul_file()
{
        string file, filename;
        string *list;
        string id, name;
        int i, n = 0;
        int status;

        list = keys(soul_list);

        for( i = 0; i < sizeof(list); i ++ )
        {
                reset_eval_cost();
                for( status = 1; status < 7; status++ )
                {
                        id = list[i];
                        name = soul_list[list[i]];
                        filename = id+"_soul"+status;
                 
                        file = read_file("/clone/enchase/equipsoul.h");
                        file = replace_string(file, "RP_NAME", name);
                        file = replace_string(file, "RP_ID", id);
                        file = replace_string(file, "RP_STATUS", to_string(status));

                        write_file("/clone/enchase/" + filename + ".c", file, 1);
                        n++;
                }
        }

        write(sprintf("%d", n) + " Files created at /clone/enchase/ .\n");
        return;
}

