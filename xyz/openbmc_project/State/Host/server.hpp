#pragma once
#include <tuple>
#include <systemd/sd-bus.h>
#include <sdbusplus/server.hpp>

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace State
{
namespace server
{

class Host
{
    public:
        /* Define all of the basic class operations:
         *     Not allowed:
         *         - Default constructor to avoid nullptrs.
         *         - Copy operations due to internal unique_ptr.
         *         - Move operations due to 'this' being registered as the
         *           'context' with sdbus.
         *     Allowed:
         *         - Destructor.
         */
        Host() = delete;
        Host(const Host&) = delete;
        Host& operator=(const Host&) = delete;
        Host(Host&&) = delete;
        Host& operator=(Host&&) = delete;
        virtual ~Host() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Host(bus::bus& bus, const char* path);

        enum class Transition
        {
            Off,
            On,
            Reboot,
        };
        enum class HostState
        {
            Off,
            Running,
        };



        /** Get value of RequestedHostTransition */
        virtual Transition requestedHostTransition() const;
        /** Set value of RequestedHostTransition */
        virtual Transition requestedHostTransition(Transition value);
        /** Get value of CurrentHostState */
        virtual HostState currentHostState() const;
        /** Set value of CurrentHostState */
        virtual HostState currentHostState(HostState value);

    /** @brief Convert a string to an appropriate enum value.
     *  @param[in] s - The string to convert in the form of
     *                 "xyz.openbmc_project.State.Host.<value name>"
     *  @return - The enum value.
     */
    static Transition convertTransitionFromString(std::string& s);
    /** @brief Convert a string to an appropriate enum value.
     *  @param[in] s - The string to convert in the form of
     *                 "xyz.openbmc_project.State.Host.<value name>"
     *  @return - The enum value.
     */
    static HostState convertHostStateFromString(std::string& s);

    private:

        /** @brief sd-bus callback for get-property 'RequestedHostTransition' */
        static int _callback_get_RequestedHostTransition(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'RequestedHostTransition' */
        static int _callback_set_RequestedHostTransition(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'CurrentHostState' */
        static int _callback_get_CurrentHostState(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'CurrentHostState' */
        static int _callback_set_CurrentHostState(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);


        static constexpr auto _interface = "xyz.openbmc_project.State.Host";
        static const vtable::vtable_t _vtable[];
        sdbusplus::server::interface::interface
                _xyz_openbmc_project_State_Host_interface;

        Transition _requestedHostTransition = Transition::Off;
        HostState _currentHostState{};

};

/* Specialization of sdbusplus::server::bindings::details::convertForMessage
 * for enum-type Host::Transition.
 *
 * This converts from the enum to a constant c-string representing the enum.
 *
 * @param[in] e - Enum value to convert.
 * @return C-string representing the name for the enum value.
 */
std::string convertForMessage(Host::Transition e);
/* Specialization of sdbusplus::server::bindings::details::convertForMessage
 * for enum-type Host::HostState.
 *
 * This converts from the enum to a constant c-string representing the enum.
 *
 * @param[in] e - Enum value to convert.
 * @return C-string representing the name for the enum value.
 */
std::string convertForMessage(Host::HostState e);

} // namespace server
} // namespace State
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

