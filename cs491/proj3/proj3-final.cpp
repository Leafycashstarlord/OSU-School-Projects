void
Forward( float th1, float th2, float th3,  float l1, float l2, glm::mat4& m1g, glm::mat4& m2g, glm::mat4& m3g )
{
    float t1 = glm::radians(th1);
    float t2 = glm::radians(th2);
    float t3 = glm::radians(th3);

    glm::mat4 len1 = glm::translate(glm::mat4(1.), glm::vec3(l1, 0, 0));
    glm::mat4 len2 = glm::translate(glm::mat4(1.), glm::vec3(l2, 0, 0));

    glm::mat4 rot1 = glm::rotate(glm::mat4(1.), t1, glm::vec3(0, 0, 1));
    glm::mat4 rot2 = glm::rotate(glm::mat4(1.), t2, glm::vec3(0, 0, 1));
    glm::mat4 rot3 = glm::rotate(glm::mat4(1.), t3, glm::vec3(0, 0, 1));

    m1g = rot1;
    m2g = m1g * (len1 * rot2);
    m3g = m2g * (len2 * rot3);
}

void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
        yourName = "Jackson Rollins";
        yourEmailAddress = "rollijac@oregonstate.edu" ;
}