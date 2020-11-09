#include "cPersonGenerator.h"
#include "SmartArray.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include <random>

cPersonGenerator::cPersonGenerator() {
	this->numNames = 0;
	this->numSurname = 0;
	this->numStreets = 0;
}
cPersonGenerator::~cPersonGenerator() {

}


bool cPersonGenerator::LoadCensusFiles(	std::string babyNameFile, std::string surnameFile, std::string streetNameFile, std::string& errorString )
{
	// TODO: Put YOUR amazing code here!
	std::ifstream ifSurnameFile(surnameFile);
	if (!ifSurnameFile.is_open())
	{
		std::cout << "Failed to open file: " << surnameFile << std::endl;
		std::cout << errorString << std::endl;
		return false;
	}
	std::string theLine;
	//skip first entry column name
	std::getline(ifSurnameFile, theLine);


	while (std::getline(ifSurnameFile, theLine))
	{
	
		std::stringstream ssLine(theLine);
		this->numSurname++;
		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				this->surnameVec.addAtEnd(token);
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}


	std::ifstream ifBabyNameFile(babyNameFile);
	if (!ifBabyNameFile.is_open())
	{
		std::cout << "Failed to open file: " << babyNameFile << std::endl;
		std::cout << errorString << std::endl;
		return false;
	}



	while (std::getline(ifBabyNameFile, theLine))
	{
		this->numNames++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				this->nameVec.addAtEnd(token);
			}
			if (tokenCount == 1) {
				this->genderVec.addAtEnd(token);
			}
			if (tokenCount == 2) {
				this->chanceVec.addAtEnd(stoi(token));
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::ifstream ifStreetNameFile(streetNameFile);
	if (!ifStreetNameFile.is_open())
	{
		std::cout << "Failed to open file: " << streetNameFile << std::endl;
		std::cout << errorString << std::endl;
		return false;
	}

	
	//skip first entry column name
	std::getline(ifStreetNameFile, theLine);
	
	
	while (std::getline(ifStreetNameFile, theLine))
	{
		std::stringstream ssLine(theLine);
		this->numStreets++;
		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 1)
			{
				this->streetNameVec.addAtEnd(token);
			}
			if (tokenCount == 2) {
				this->streetTypeVec.addAtEnd(token);
			}
			if (tokenCount == 3) {
				this->streetDirec.addAtEnd(token);
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}


	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void) {
	return this->numNames;
}
unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void) {
	return this->numSurname;
}
unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void) {
	return this->numStreets;
}

// Randomly generates a person from the data
// Returns 0, NULL, or nullptr if it can't do this. 
//#include <random>
cPerson* cPersonGenerator::generateRandomPerson(void) {

	cPerson* newPerson = new cPerson();
	std::random_device rd;
	std::uniform_int_distribution<int> dist(100000000, 999999999);
	newPerson->SIN = dist(rd);

	std::uniform_int_distribution<int> distName(0, nameVec.getSize() - 1);
	int nameGender = distName(rd);
	newPerson->first = nameVec.getAt(nameGender);
	newPerson->middle = nameVec.getAt(distName(rd));
	std::uniform_int_distribution<int> surnameDist(0, surnameVec.getSize() - 1);
	newPerson->last = surnameVec.getAt(surnameDist(rd));
	std::uniform_int_distribution<int> streetDist(0, streetNameVec.getSize() - 1);
	newPerson->streetName = streetNameVec.getAt(streetDist(rd));
	std::uniform_int_distribution<int> streetDirectDist(0, streetDirec.getSize() - 1);
	newPerson->streetDirection = streetDirec.getAt(streetDirectDist(rd));
	std::uniform_int_distribution<int> streettypeDist(0, streetTypeVec.getSize() - 1);
	newPerson->streetType = streetTypeVec.getAt(streettypeDist(rd));
	std::uniform_int_distribution<int> streetnumDist(0, 100000);
	newPerson->streetNumber = streetnumDist(rd);
	std::uniform_int_distribution<int> ageDist(0, 120);
	newPerson->age = ageDist(rd);

	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char number[10] = { '0', '1','2','3','4','5','6','7','8','9' };
	std::uniform_int_distribution<int> alphaDist(0, 25);
	std::uniform_int_distribution<int> numberDist(0, 9);

		
	newPerson->postalCode[0] = toupper(alphabet[alphaDist(rd)]);
	newPerson->postalCode[1] = number[numberDist(rd)];
	newPerson->postalCode[2] = toupper(alphabet[alphaDist(rd)]);
	newPerson->postalCode[3] = number[numberDist(rd)];
	newPerson->postalCode[4] = toupper(alphabet[alphaDist(rd)]);
	newPerson->postalCode[5] = number[numberDist(rd)];
	//needs to be zero terminated 
	newPerson->postalCode[6] = '\0';

	std::string provincesArray[] = { "Alberta", "British Columbia", "Ontario", "Quebec", "Nova Scotia", "New Brunswick", "Manitoba", "Prince Edward Island", "Saskatchewan", "Newfoundland and labrador" };
	std::uniform_int_distribution<int> provDist(0, 9);

	newPerson->province = provincesArray[provDist(rd)];
	std::string city_names[] = { "Aberdeen", "Abilene", "Akron", "Albany", "Albuquerque", "Alexandria", "Allentown", "Amarillo", "Anaheim", "Anchorage", "Ann Arbor", "Antioch", "Apple Valley", "Appleton", "Arlington", "Arvada", "Asheville", "Athens", "Atlanta", "Atlantic City", "Augusta", "Aurora", "Austin", "Bakersfield", "Baltimore", "Barnstable", "Baton Rouge", "Beaumont", "Bel Air", "Bellevue", "Berkeley", "Bethlehem", "Billings", "Birmingham", "Bloomington", "Boise", "Boise City", "Bonita Springs", "Boston", "Boulder", "Bradenton", "Bremerton", "Bridgeport", "Brighton", "Brownsville", "Bryan", "Buffalo", "Burbank", "Burlington", "Cambridge", "Canton", "Cape Coral", "Carrollton", "Cary", "Cathedral City", "Cedar Rapids", "Champaign", "Chandler", "Charleston", "Charlotte", "Chattanooga", "Chesapeake", "Chicago", "Chula Vista", "Cincinnati", "Clarke County", "Clarksville", "Clearwater", "Cleveland", "College Station", "Colorado Springs", "Columbia", "Columbus", "Concord", "Coral Springs", "Corona", "Corpus Christi", "Costa Mesa", "Dallas", "Daly City", "Danbury", "Davenport", "Davidson County", "Dayton", "Daytona Beach", "Deltona", "Denton", "Denver", "Des Moines", "Detroit", "Downey", "Duluth", "Durham", "El Monte", "El Paso", "Elizabeth", "Elk Grove", "Elkhart", "Erie", "Escondido", "Eugene", "Evansville", "Fairfield", "Fargo", "Fayetteville", "Fitchburg", "Flint", "Fontana", "Fort Collins", "Fort Lauderdale", "Fort Smith", "Fort Walton Beach", "Fort Wayne", "Fort Worth", "Frederick", "Fremont", "Fresno", "Fullerton", "Gainesville", "Garden Grove", "Garland", "Gastonia", "Gilbert", "Glendale", "Grand Prairie", "Grand Rapids", "Grayslake", "Green Bay", "GreenBay", "Greensboro", "Greenville", "Gulfport-Biloxi", "Hagerstown", "Hampton", "Harlingen", "Harrisburg", "Hartford", "Havre de Grace", "Hayward", "Hemet", "Henderson", "Hesperia", "Hialeah", "Hickory", "High Point", "Hollywood", "Honolulu", "Houma", "Houston", "Howell", "Huntington", "Huntington Beach", "Huntsville", "Independence", "Indianapolis", "Inglewood", "Irvine", "Irving", "Jackson", "Jacksonville", "Jefferson", "Jersey City", "Johnson City", "Joliet", "Kailua", "Kalamazoo", "Kaneohe", "Kansas City", "Kennewick", "Kenosha", "Killeen", "Kissimmee", "Knoxville", "Lacey", "Lafayette", "Lake Charles", "Lakeland", "Lakewood", "Lancaster", "Lansing", "Laredo", "Las Cruces", "Las Vegas", "Layton", "Leominster", "Lewisville", "Lexington", "Lincoln", "Little Rock", "Long Beach", "Lorain", "Los Angeles", "Louisville", "Lowell", "Lubbock", "Macon", "Madison", "Manchester", "Marina", "Marysville", "McAllen", "McHenry", "Medford", "Melbourne", "Memphis", "Merced", "Mesa", "Mesquite", "Miami", "Milwaukee", "Minneapolis", "Miramar", "Mission Viejo", "Mobile", "Modesto", "Monroe", "Monterey", "Montgomery", "Moreno Valley", "Murfreesboro", "Murrieta", "Muskegon", "Myrtle Beach", "Naperville", "Naples", "Nashua", "Nashville", "New Bedford", "New Haven", "New London", "New Orleans", "New York", "New York City", "Newark", "Newburgh", "Newport News", "Norfolk", "Normal", "Norman", "North Charleston", "North Las Vegas", "North Port", "Norwalk", "Norwich", "Oakland", "Ocala", "Oceanside", "Odessa", "Ogden", "Oklahoma City", "Olathe", "Olympia", "Omaha", "Ontario", "Orange", "Orem", "Orlando", "Overland Park", "Oxnard", "Palm Bay", "Palm Springs", "Palmdale", "Panama City", "Pasadena", "Paterson", "Pembroke Pines", "Pensacola", "Peoria", "Philadelphia", "Phoenix", "Pittsburgh", "Plano", "Pomona", "Pompano Beach", "Port Arthur", "Port Orange", "Port Saint Lucie", "Port St. Lucie", "Portland", "Portsmouth", "Poughkeepsie", "Providence", "Provo", "Pueblo", "Punta Gorda", "Racine", "Raleigh", "Rancho Cucamonga", "Reading", "Redding", "Reno", "Richland", "Richmond", "Richmond County", "Riverside", "Roanoke", "Rochester", "Rockford", "Roseville", "Round Lake Beach", "Sacramento", "Saginaw", "Saint Louis", "Saint Paul", "Saint Petersburg", "Salem", "Salinas", "Salt Lake City", "San Antonio", "San Bernardino", "San Buenaventura", "San Diego", "San Francisco", "San Jose", "Santa Ana", "Santa Barbara", "Santa Clara", "Santa Clarita", "Santa Cruz", "Santa Maria", "Santa Rosa", "Sarasota", "Savannah", "Scottsdale", "Scranton", "Seaside", "Seattle", "Sebastian", "Shreveport", "Simi Valley", "Sioux City", "Sioux Falls", "South Bend", "South Lyon", "Spartanburg", "Spokane", "Springdale", "Springfield", "St. Louis", "St. Paul", "St. Petersburg", "Stamford", "Sterling Heights", "Stockton", "Sunnyvale", "Syracuse", "Tacoma", "Tallahassee", "Tampa", "Temecula", "Tempe", "Thornton", "Thousand Oaks", "Toledo", "Topeka", "Torrance", "Trenton", "Tucson", "Tulsa", "Tuscaloosa", "Tyler", "Utica", "Vallejo", "Vancouver", "Vero Beach", "Victorville", "Virginia Beach", "Visalia", "Waco", "Warren", "Washington", "Waterbury", "Waterloo", "West Covina", "West Valley City", "Westminster", "Wichita", "Wilmington", "Winston", "Winter Haven", "Worcester", "Yakima", "Yonkers", "York", "Youngstown" };

	std::uniform_int_distribution<int> cityDist(0, city_names->length()-1);
	newPerson->city = city_names[cityDist(rd)];

	std::uniform_int_distribution<int> sexDist(0, 5);
	int genderNum = sexDist(rd);

	std::string gender = genderVec.getAt(nameGender);
	if (gender == "M") {
		newPerson->gender = cPerson::eGenderType::MALE;
	}
	if (gender == "F") {
		newPerson->gender = cPerson::eGenderType::FEMALE;
	}
	
	return newPerson;
}