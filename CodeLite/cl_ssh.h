//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : cl_ssh.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef CLSSH_H
#define CLSSH_H

#include <wx/string.h>
#include <errno.h>
#include "cl_exception.h"
#include "codelite_exports.h"
#include <wx/sharedptr.h>

// We do it this way to avoid exposing the include to ssh/libssh.h to files including this header
struct ssh_session_struct;
typedef struct ssh_session_struct* SSHSession_t;

class WXDLLIMPEXP_CL clSSH
{
    wxString     m_host;
    wxString     m_username;
    wxString     m_password;
    int          m_port;
    SSHSession_t m_session;
    bool         m_connected;
    
public:
    typedef wxSharedPtr<clSSH> Ptr_t;
    
public:
    clSSH(const wxString& host, const wxString& user, const wxString& pass, int port = 22);
    clSSH();
    virtual ~clSSH();

    /**
     * @brief connect to the remote server
     */
    void Connect() throw (clException);

    /**
     * @brief authenticate the server
     * @param [output] message in case the authentication failed, prompt the user with the message
     * @return true if the server could be authenticated, otherwise return false.
     * In case an error occurs, throw a clException
     */
    bool AuthenticateServer(wxString& message) throw (clException);

    /**
     * @brief accepts the server authentication and add it to the "known_hosts"
     */
    void AcceptServerAuthentication() throw (clException);

    /**
     * @brief login to the server with the user credentials
     * @return true if we managed to login
     * @throw clException incase something really bad happened
     */
    bool LoginPassword(bool throwExc = true) throw (clException);
    
    /**
     * @brief login using public key
     * @return true if we managed to login
     * @throw clException incase something really bad happened
     */
    bool LoginPublicKey(bool throwExc = true) throw (clException);
    
    /**
     * @brief login using interactive-keyboard method
     * @return true if we managed to login
     * @throw clException incase something really bad happened
     */
    bool LoginInteractiveKBD(bool throwExc = true) throw (clException);
    
    /**
     * @brief try to login using all the methods we support (interactive-kbd, user/pass and public key)
     */
    void Login() throw (clException);
    
    /**
     * @brief close the SSH session
     * IMPORTANT: this will invalidate all other channels (like: scp)
     */
    void Close();
    
    SSHSession_t GetSession() {
        return m_session;
    }
    
    void SetPassword(const wxString& password) {
        this->m_password = password;
    }
    void SetPort(int port) {
        this->m_port = port;
    }

    const wxString& GetPassword() const {
        return m_password;
    }
    int GetPort() const {
        return m_port;
    }
    void SetHost(const wxString& host) {
        this->m_host = host;
    }
    void SetUsername(const wxString& username) {
        this->m_username = username;
    }
    const wxString& GetHost() const {
        return m_host;
    }
    const wxString& GetUsername() const {
        return m_username;
    }
};

#endif // CLSSH_H