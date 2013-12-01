//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#include <mlk/mlk.h>
#include <twl/network/network.h>

#include <iostream>


void exit_with(const std::string& msg)
{std::cout << msg << std::endl; std::exit(EXIT_FAILURE);}


std::string make_page(const twl::server_info& info)
{
	std::stringstream strm;
	if(!info.is_valid())
	{
		strm << "This server seems to be <span style=\"color:#921100\">DOWN</span>.";
		return strm.str();
	}

	strm << "This server is <span style=\"color:#023300\">UP</span>.<br /><br />";
	strm << "<table style=\"margin:auto;\">";
	strm << "<tr><td class=\"property\">Name</td><td class=\"value\">" << info.name <<"</td></tr>";
	strm << "<tr><td class=\"property\">Version</td><td class=\"value\">" << info.version <<"</td></tr>";
	strm << "<tr><td class=\"property\">Gametype</td><td class=\"value\">" << info.game_type <<"</td></tr>";
	strm << "<tr><td class=\"property\">Map</td><td class=\"value\">" << info.map_name <<"</td></tr>";
	strm << "<tr><td class=\"property\">Ping(ms)</td><td class=\"value\">" << info.ping <<"</td></tr>";
	strm << "</table><br />";
	strm << "<h3>Players</h3>";
	strm << "<table style=\"margin:auto\">";

	if(!info.num_clients)
		strm << "No players online.";
	else
	{
		strm << "<tr><td class=\"player_td\">Name</td><td class=\"player_td\">Clan</td>"
			 <<"<td class=\"player_td\">Score</td><td class=\"player_td\">Country</td><td class=\"player_td\">Playing?</td></tr>";
		for(auto& a : info.clients)
			strm << "<tr><td>" << a.name << "</td><td>" << a.clan << "</td><td>"
				 << a.score << "</td><td>" << a.country << "</td><td>" << (a.is_player ? "Yes" : "No") << "</td></tr>";
	}
	strm << "</table>";
	return strm.str();
}


int main(int argc, char* argv[])
{
	if(argc != 2)
		exit_with("invalid amount of arguments passed");

	// remove possible prefixes
	std::vector<std::string> invalid_strs{"www.", "https", "http", "sftp", "ftp", "ssh", "://"};
	auto ip_str(std::string{argv[1]});
	for(auto& a : invalid_strs)
		mlk::stl_string::erase_all(a, ip_str);

	mlk::ntw::ip_address addr{ip_str};
	if(!addr.is_valid())
		exit_with("invalid address passed");


	// do the actually server action
	twl::server srv{addr};
	auto info(srv.get_info());

	// format the output page and check info
	auto tm_s(mlk::tm::time_pnt()); // take time
	std::cout << make_page(info);
	auto tm_e(mlk::tm::time_pnt());

	// print the duration as float
	std::cout << "<br /><br /><span style=\"font-size:9pt\">Generated information-table in "
			  << mlk::tm::duration_as<float>(tm_s, tm_e) << " ms</span>";

	return 0;
}
